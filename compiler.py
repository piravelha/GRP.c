from _parser import parser
from lark import Token, Tree

needed_symbols = {}

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
    if final and not kwargs["paren"]:
        code += "    return 0;\n"
    return code

def compile_char(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    code += f"    // push '{value}'\n"
    if cur_func == "main":
        code += f"    pushChar(&_stack, '{value}');\n"
    else:
        code += f"    pushChar(_stack, '{value}');\n"
    final = kwargs["final"]
    if final and not kwargs["paren"]:
        code += "    return 0;\n"
    return code

def compile_string(code, value, **kwargs):
    chars = [Token("CHAR", c) for c in value[1:-1]]
    return compile_array(code, *chars, **(kwargs.copy()))

def compile_float(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    code += f"    // push {value}\n"
    if cur_func == "main":
        code += f"    pushFloat(&_stack, {value});\n"
    else:
        code += f"    pushFloat(_stack, {value});\n"
    final = kwargs["final"]
    if final and not kwargs["paren"]:
        code += "    return 0;\n"
    return code

def compile_name(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    final = kwargs["final"]
    if final and "_var_" + value == cur_func:
        code += f"    return 1;\n"
        return code
    if cur_func == "main":
        code += f"    trampoline(_var_{value}, &_stack);\n"
    else:
        code += f"    trampoline(_var_{value}, _stack);\n"
    return code


operator_lookup = {
    "<?": "_var_Print",
    "?": "_var_Show",
    "+": "_var_Plus",
    "^+": "_var_Conjuage",
    "-": "_var_Minus",
    "^-": "_var_Negate",
    "*": "_var_Times",
    "^*": "_var_Signum",
    "/": "_var_Div",
    "^/": "_var_Reciprocal",
    "%": "_var_Mod",
    "**": "_var_Power",
    "^**": "_var_Exp",
    "^//": "_var_Sqrt",
    "//": "_var_Root",
    "-|": "_var_Floor",
    "+|": "_var_Ceil",
    "=-=": "_var_Min",
    "=+=": "_var_Max",
    "|^|": "_var_Abs",
    "===": "_var_Depth",
    "<": "_var_Lt",
    ">": "_var_Gt",
    "<=": "_var_Lte",
    ">=": "_var_Gte",
    "=": "_var_Eq",
    "++": "_var_Concat",
    ".": "_var_Dup",
    "<->": "_var_Flip",
    "<$>": "_var_Map",
    "<&>": "_var_Filter",
    "<.>": "_var_Reduce",
    "<*": "_var_Head",
    "*>>": "_var_Tail",
    "#": "_var_Length",
    ":>": "_var_Cons",
}

def compile_operator(code, value, **kwargs):
    cur_func = kwargs["cur_func"]
    code += f"    // operator {value}\n"
    amper = "&" if cur_func == "main" else ""
    
    if value in operator_lookup:
        code += f"    trampoline({operator_lookup[value]}, {amper}_stack);\n"
    else:
        assert False, f"Unrecognized operator: '{value}'"
    final = kwargs["final"]
    if final:
        code += "    return 0;\n"
    return code

def compile_array(code, *values, **kwargs):
    cur_func = kwargs["cur_func"]
    code += "    // push array\n"
    for val in reversed(values):
        kwargs["paren"] = True
        code = compile_tree(code, val, **(kwargs.copy()))
    if cur_func == "main":
        code += f"    pushArray(&_stack, {len(values)});\n"
    else:
        code += f"    pushArray(_stack, {len(values)});\n"
    if not kwargs["paren"] and kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_symbol(code, name, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    code += f"    // symbol\n"
    code += f"    Data _var_{name} = pop({amper}_stack);\n"
    if not kwargs["paren"] and kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_symbol_call(code, name, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    if not needed_symbols.get(kwargs["cur_func"], []):
        needed_symbols[kwargs["cur_func"]] = []
    needed_symbols.get(kwargs["cur_func"], []).append(f"_var_{name}")
    code += f"    // symbol call\n"
    code += f"    push({amper}_stack, _var_{name});\n"
    if not kwargs["paren"] and kwargs["final"]:
        code += "    return 0;\n"
    return code

def compile_quote(code, expr, **kwargs):
    cur_func = kwargs["cur_func"]
    u = unique()
    code = code.split("// start\n", 1)
    func = "// start\n"
    func += f"int quote{u}(Stack *_stack, Data *needed) {{\n"
    kwargs["cur_func"] = f"quote{u}"
    func = compile_tree(func, expr, **(kwargs.copy()))
    func += f"}}\n"
    code.insert(1, func)
    code = "\n".join(code)
    code += f"    // quoting\n"
    code += f"    Data funcData{u} = createFunction();\n"
    needed = needed_symbols.get(kwargs["cur_func"], [])
    code += f"    Data *needed{u} = malloc({len(needed)} * sizeof(Data));\n"
    for i, need in enumerate(needed):
        code += f"    needed{u}[{i}] = {need};\n"
    code += f"    funcData{u}.quoteValue.needed = needed{u};\n"
    code += f"    funcData{u}.quoteValue.funcValue = quote{u};\n"
    if cur_func == "main":
        code += f"    push(&_stack, funcData{u});\n"
    else:
        code += f"    push(_stack, funcData{u});\n"
    if not kwargs["paren"] and kwargs["final"]:
        code += "    return 0;\n"
    code = code.split(f"int quote{u}(Stack *_stack, Data *needed) {{\n")
    unpack = ""
    for i, need in enumerate(needed):
        unpack += f"    Data {need} = needed[{i}];\n"
    code[1] = unpack + code[1]
    code = f"int quote{u}(Stack *_stack, Data *needed) {{\n".join(code)
    if not needed_symbols.get(cur_func):
        needed_symbols[cur_func] = []
    needed_symbols[cur_func] += needed_symbols.get(f"quote{u}", [])
    return code

def compile_splice(code, expr, **kwargs):
    cur_func = kwargs["cur_func"]
    amper = "&" if cur_func == "main" else ""
    u = unique()
    code += f"    // splicing\n"
    kwargs["paren"] = True
    code = compile_tree(code, expr, **(kwargs.copy()))
    code += f"    Data funcData{u} = pop({amper}_stack);\n"
    code += f"    if (funcData{u}.type == TYPE_FUNC) {{\n"
    code += f"        funcData{u}.quoteValue.funcValue({amper}_stack, funcData{u}.quoteValue.needed);\n"
    code += f"    }}\n"
    return code
    
def compile_variable(code, *args, **kwargs):
    if len(args) == 3:
        name, _, expr = args
    else:
        name, expr = args
    old_cur_func = kwargs["cur_func"]
    code = code.split("// start\n", 1)
    func = "// start\n"
    func += f"int _var_{name}(Stack *_stack) {{\n"
    kwargs["cur_func"] = f"_var_{name}"
    func = compile_expression(func, expr, **(kwargs.copy()))
    func += f"}}\n"
    func = func.replace("// start\n", "") + "\n// start\n"
    code.insert(1, func)
    code = "\n".join(code)
    code = code.split("// top\n", 1)
    code.insert(1, f"// top\nint _var_{name}(Stack *_stack);\n")
    code = "\n".join(code)
    kwargs["cur_func"] = old_cur_func
    return code

def compile_if(code, *conditions, **kwargs):
    cur_func = kwargs["cur_func"]
    u = unique()
    amper = "&" if cur_func == "main" else ""
    for tree in conditions[:-1]:
        cond, then = tree.children
        cond_u = unique()
        old_paren = kwargs["paren"]
        kwargs["paren"] = True
        code = compile_tree(code, cond, **(kwargs.copy()))
        code += f"    Data condition{cond_u} = pop({amper}_stack);\n"
        code += f"    if (!condition{cond_u}.type == TYPE_INT || condition{cond_u}.intValue) {{\n"
        code += f"        freeData(&condition{cond_u});\n"
        kwargs["paren"] = old_paren
        code = compile_tree(code, then, **(kwargs.copy()))
        code += f"    }} else {{\n"
    true = conditions[-1]
    code = compile_tree(code, true, **(kwargs.copy()))
    code += f"    }}\n" * round((len(conditions)) / 2)
    return code

def compile_paren(code, expr, **kwargs):
    kwargs["paren"] = True
    return compile_expression(code, expr, **(kwargs.copy()))

def compile_expression(code, *atoms, **kwargs):
    kwargs["final"] = False
    paren = kwargs.get("paren", False)
    for i, at in enumerate(atoms):
        if i == len(atoms) - 1 and not paren:
            kwargs["final"] = True
        code = compile_tree(code, at, **(kwargs.copy()))
    return code

def save_operator(dec):
    global operator_lookup
    children = dec.children
    if len(children) == 3:
        name, op, *_ = children
        operator_lookup[op] = f"_var_{name}"

def compile_program(code, *decls, **kwargs):
    if not len(decls):
        return code
    [save_operator(dec) for dec in decls if dec.data == "variable"]
    for dec in decls:
        if dec.data != "expression":
            code = compile_tree(code, dec, **(kwargs.copy()))
    if decls[-1].data == "expression":
        code = compile_tree(code, decls[-1], **(kwargs.copy()))
    return code

def compile_tree(code, tree, **kwargs):
    if isinstance(tree, Token):
        if tree.type == "INT":
            return compile_int(code, tree.value, **(kwargs.copy()))
        if tree.type == "CHAR":
            return compile_char(code, tree.value, **(kwargs.copy()))
        if tree.type == "STRING":
            return compile_string(code, tree.value, **(kwargs.copy()))
        if tree.type == "FLOAT":
            return compile_float(code, tree.value, **(kwargs.copy()))
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
            return compile_paren(code, *tree.children, **(kwargs.copy()))        
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
    code += "#include <stdlib.h>\n"
    code += "#include \"lib.h\"\n"
    code += "#include \"tostring.h\"\n"
    code += "#include \"operations.h\"\n\n"
    code += "// top\n"
    code += "// start\n"
    code += "int main() {\n"
    code += "    Stack _stack;\n"
    code += "    initStack(&_stack);\n"
    code = compile_tree(code, tree, cur_func="main", final=False, paren=False)
    if code.rstrip().endswith("    return 0;"):
        code = code[:-14]
    code += "    freeStack(&_stack);\n"
    code += "}\n"
    return code

with open("main.grp") as f:
    source_code = f.read()

with open("Core.grp") as f:
    core_code = f.read()

compiled = compile_source_code(core_code + "\n\n" + source_code)

with open("main.c", "w") as f:
    f.write(compiled)