from _parser import parser
from lark import Token, Tree

unique_val = -1
def unique():
    global unique_val
    unique_val += 1
    return unique_val

def remove_returns(code):
    new_code = []
    for line in code.splitlines():
        if line.strip() == "return 0;" or line.strip() == "return 1;":
            continue
        new_code.append(line)
    return "\n".join(new_code) + "\n"

def compile_int(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    code += f"    // push {value}\n"
    if cur_func == "main":
        code += f"    pushInt(&_stack, {value});\n"
    else:
        code += f"    pushInt(_stack, {value});\n"
    final = kwargs["final"]
    if final:
        code += "    return 0;\n"
    return code

def compile_name(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    final = kwargs["final"]
    if final and "_var_" + value == cur_func:
        code += f"    return 1;"
        return code
    if cur_func == "main":
        code += f"    trampoline(_var_{value}, &_stack);\n"
    else:
        code += f"    trampoline(_var_{value}, _stack);\n"
    return code

def compile_operator(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    code += f"    // operator {value}\n"
    amper = "&" if cur_func == "main" else ""
    if value == "<?":
        code += f"    printData(pop({amper}_stack));\n"
    elif value == "+":
        code += f"    plusOperation({amper}_stack);\n"
    elif value == "-":
        code += f"    minusOperation({amper}_stack);\n"
    elif value == "*":
        code += f"    timesOperation({amper}_stack);\n"
    elif value == "/":
        code += f"    divOperation({amper}_stack);\n"
    elif value == "=":
        code += f"    eqOperation({amper}_stack);\n"
    elif value == "<":
        code += f"    ltOperation({amper}_stack);\n"
    elif value == ">":
        code += f"    gtOperation({amper}_stack);\n"
    elif value == "<=":
        code += f"    lteOperation({amper}_stack);\n"
    elif value == ">=":
        code += f"    gteOperation({amper}_stack);\n"
    elif value == "++":
        code += f"    concatOperation({amper}_stack);\n"
    elif value == ".":
        code += f"    duplicateOperation({amper}_stack);\n"
    elif value == ",":
        u = unique()
        code += f"    Data popped{u} = pop({amper}_stack);\n"
        code += f"    freeData(&popped{u});\n"
    elif value == "<$>":
        code += f"    mapOperation({amper}_stack);\n"
    else:
        assert False, f"Unrecognized operator: {value}"
    final = kwargs["final"]
    if final:
        code += "    return 0;\n"
    return code

def compile_array(code, *values, **kwargs):
    cur_func = kwargs["cur_func"]
    code += "    // push array\n"
    for val in reversed(values):
        code = compile_tree(code, val, **(kwargs.copy()))
    if cur_func == "main":
        code += f"    pushArray(&_stack, {len(values)});\n"
    else:
        code += f"    pushArray(_stack, {len(values)});\n"
    if kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_symbol(code, name, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    code += f"    // symbol\n"
    code += f"    Data _var_{name} = pop({amper}_stack);\n"
    if kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_symbol_call(code, name, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    code += f"    // symbol call\n"
    code += f"    push({amper}_stack, _var_{name});\n"
    if kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_quote(code, expr, **kwargs):
    cur_func = kwargs["cur_func"]
    u = unique()
    code = code.split("// start\n")
    func = f"int quote{u}(Stack *_stack) {{\n"
    kwargs["cur_func"] = f"quote{u}"
    func = compile_tree(func, expr, **(kwargs.copy()))
    func += f"}}\n"
    func += "// start\n"
    code.insert(1, func)
    code = "\n".join(code)
    code += f"    // quoting\n"
    code += f"    Data funcData{u} = createFunction();\n"
    code += f"    funcData{u}.funcValue = quote{u};\n"
    if cur_func:
        code += f"    push(&_stack, funcData{u});\n"
    else:
        code += f"    push(_stack, funcData{u});\n"
    return code

def compile_splice(code, expr, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    u = unique()
    code += f"    // splicing\n"
    kwargs["paren"] = True
    expr = compile_tree("", expr, **(kwargs.copy()))
    expr = remove_returns(expr)
    code += expr
    code += f"    Data funcData{u} = pop({amper}_stack);\n"
    code += f"    if (funcData{u}.type == TYPE_FUNC) {{\n"
    code += f"        funcData{u}.funcValue({amper}_stack);\n"
    code += f"    }}\n"
    return code
    
def compile_variable(code, name, expr, **kwargs):
    code = code.split("// start\n")
    func = f"int _var_{name}(Stack *_stack) {{\n"
    kwargs["cur_func"] = f"_var_{name}"
    func = compile_tree(func, expr, **(kwargs.copy()))
    func += f"}}\n"
    func += "// start\n"
    code.insert(1, func)
    code = "\n".join(code)
    return code

def compile_if(code, true, false, **kwargs):
    cur_func = kwargs["cur_func"]
    kwargs["final"] = False
    u = unique()
    amper = "&" if cur_func == "main" else ""
    code += f"    Data condition{u} = pop({amper}_stack);\n"
    code += f"    if (condition{u}.type == TYPE_INT && !condition{u}.intValue) {{\n"
    code += f"        freeData(&condition{u});\n"
    true = compile_tree("", true, **(kwargs.copy()))
    true = "\n".join(["    " + l for l in true.splitlines()]) + "\n"
    false = compile_tree("", false, **(kwargs.copy()))
    false = "\n".join(["    " + l for l in false.splitlines()]) + "\n"
    code += false
    code += f"    }} else {{\n"
    code += f"        freeData(&condition{u});\n"
    code += true
    code += f"    }}\n"
    return code

def compile_paren(code, expr, **kwargs):
    kwargs["paren"] = True
    return compile_expression(code, expr, **(kwargs.copy()))

def compile_expression(code, *atoms, **kwargs):
    paren = kwargs.get("paren", False)
    for i, at in enumerate(atoms):
        if i == len(atoms) - 1 and not paren:
            kwargs["final"] = True
        code = compile_tree(code, at, **(kwargs.copy()))
    if not paren:
        kwargs["final"] = False
    return code

def compile_program(code, *decls, **kwargs):
    for dec in decls:
        code = compile_tree(code, dec, **(kwargs.copy()))
    return code

def compile_tree(code, tree, **kwargs):
    if isinstance(tree, Token):
        if tree.type == "INT":
            return compile_int(code, tree.value, **(kwargs.copy()))
        if tree.type == "NAME":
            return compile_name(code, tree.value, **(kwargs.copy()))
        if tree.type == "OPERATOR":
            return compile_operator(code, tree.value, **(kwargs.copy()))
        assert False, f"Unimplemented: {tree.type}"
    else:
        if tree.data == "array":
            return compile_array(code, *tree.children, **(kwargs.copy()))
        if tree.data == "symbol":
            return compile_symbol(code, *tree.children, **(kwargs.copy()))
        if tree.data == "symbol_call":
            return compile_symbol_call(code, *tree.children, **(kwargs.copy()))
        if tree.data == "quote":
            return compile_quote(code, *tree.children, **(kwargs.copy()))
        if tree.data == "splice":
            return compile_splice(code, *tree.children, **(kwargs.copy()))
        if tree.data == "if":
            return compile_if(code, *tree.children, **(kwargs.copy()))
        if tree.data == "paren":
            return compile_paren(code, *tree.children, **kwargs)        
        if tree.data == "expression":
            return compile_expression(code, *tree.children, **(kwargs.copy()))
        if tree.data == "variable":
            return compile_variable(code, *tree.children, **(kwargs.copy()))
        if tree.data == "program":
            return compile_program(code, *tree.children, **(kwargs.copy()))
    assert False, f"Unimplemented: {tree.data}"

def compile_source_code(source_code):
    tree = parser.parse(source_code)
    code = "#include <stdio.h>\n"
    code += "#include \"lib.h\"\n"
    code += "#include \"tostring.h\"\n"
    code += "#include \"operations.h\"\n\n"
    code += "// start\n"
    code += "int main() {\n"
    code += "    Stack _stack;\n"
    code += "    initStack(&_stack);\n"
    code = compile_tree(code, tree, cur_func="main", final=False)
    if code.rstrip().endswith("    return 0;"):
        code = code[:-14]
    code += "    freeStack(&_stack);\n"
    code += "}\n"
    return code

with open("main.grp") as f:
    source_code = f.read()

compiled = compile_source_code(source_code)

with open("main.c", "w") as f:
    f.write(compiled)