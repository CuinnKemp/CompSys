def reformatSegment(segment, offset):
    if (segment == "this"):
        return "THIS"

    if (segment == "that"):
        return "THAT"

    if (segment == "argument"):
        return "ARG"
    
    if (segment == "local"):
        return "LCL"
    
    if (segment == "static"):
        return str(16+offset)

    if (segment == "pointer"):
        return "R" + str(3 + offset)

    if (segment == "temp"):
        return "R" + str(5 + offset)

    if (segment == "constant"):
        return str(offset)
    
    return ""

class VMTranslator:
    labelCounter = 0
    
    def newLabel():
        retString = str(labelCounter)
        labelCounter += 1
        return retString

    def vm_push(segment, offset):
        '''Generate Hack Assembly code for a VM push operation'''
        refSeg = reformatSegment(segment, offset)
        retString = ""
        if (segment == "constant" or segment == "static" or segment == "pointer" or segment == "temp"):
            retString += "@" + refSeg + "\n"
            if segment == "constant":
                retString += "D = A\n"
            else:
                retString += "D = M\n"
        elif (segment == "local" or segment == "this" or segment == "that" or segment == "argument"):
            retString += "@" + refSeg + "\n"
            retString += "D = M\n"
            retString += "@" + str(offset) + "\n"
            retString += "A = D + A\n"
            retString += "D=M\n"
        
        retString += "@SP\n"
        retString += "A=M\n"
        retString += "M=D\n"
        retString += "@SP\n"
        retString += "M = M+1"

        return retString

    def vm_pop(segment, offset):
        '''Generate Hack Assembly code for a VM pop operation'''
        refSeg = reformatSegment(segment, offset)
        retString = "@" + refSeg + "\n"
        
        if (segment == "static" or segment == "temp" or segment == "pointer"):
            retString += "D = A\n"
        elif (segment == "local" or segment == "this" or segment == "that" or segment == "argument"):
            retString += "D = M\n"
            retString += "@" + str(offset) + "\n"
            retString += "D = D + A\n"

        retString += "@R13\n"
        retString += "M = D\n"
        retString += "@SP\n"
        retString += "AM = M -1\n"
        retString += "D=M\n"
        retString += "@R13\n"
        retString += "A=M\n"
        retString += "M=D"

        return retString

    def vm_add():
        '''Generate Hack Assembly code for a VM add operation'''
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "M = D + M"

        return retString

    def vm_sub():
        '''Generate Hack Assembly code for a VM sub operation'''
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "M = M - D"

        return retString

    def vm_neg():
        '''Generate Hack Assembly code for a VM neg operation'''
        retString = "@SP\n"
        retString += "A = M-1\n"
        retString += "M = !M\n"
        retString += "M = M + 1"

        return retString

    def vm_eq():
        '''Generate Hack Assembly code for a VM eq operation'''
        label = VMTranslator.newLabel()
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "D = M - D\n"
        retString += "@EQ.true" + label + "\n"
        retString += "D;JEQ\n"
        retString += "@SP\n"
        retString += "A = M-1\n"
        retString += "M = 0\n"
        retString += "@EQ.skip" + label + "\n"
        retString += "0;JMP\n"
        retString += "(EQ.true"+ label +")\n"
        retString += "M = -1\n"
        retString += "(EQ.skip"+ label + ")"
        return retString

    def vm_gt():
        '''Generate Hack Assembly code for a VM gt operation'''
        label = VMTranslator.newLabel()
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "D = M - D\n"
        retString += "@GT.true" + label + "\n"
        retString += "D;JGT\n"
        retString += "@SP\n"
        retString += "A = M-1\n"
        retString += "M = 0\n"
        retString += "@GT.skip" + label + "\n"
        retString += "0;JMP\n"
        retString += "(GT.true"+ label +")\n"
        retString += "M = -1\n"
        retString += "(GT.skip"+ label + ")"
        return retString

    def vm_lt():
        '''Generate Hack Assembly code for a VM lt operation'''
        label = VMTranslator.newLabel()
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "D = M - D\n"
        retString += "@LT.true" + label + "\n"
        retString += "D;JLT\n"
        retString += "@SP\n"
        retString += "A = M-1\n"
        retString += "M = 0\n"
        retString += "@LT.skip" + label + "\n"
        retString += "0;JMP\n"
        retString += "(LT.true"+ label +")\n"
        retString += "M = -1\n"
        retString += "(LT.skip"+ label + ")"
        return retString

    def vm_and():
        '''Generate Hack Assembly code for a VM and operation'''
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "M = M&D"
        return retString

    def vm_or():
        '''Generate Hack Assembly code for a VM or operation'''
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "A = A-1\n"
        retString += "M = M|D"
        return retString

    def vm_not():
        '''Generate Hack Assembly code for a VM not operation'''
        '''Generate Hack Assembly code for a VM or operation'''
        retString = "@SP\n"
        retString += "A = M-1\n"
        retString += "M = !M"
        return retString

    def vm_label(label):
        '''Generate Hack Assembly code for a VM label operation'''
        retString = "(" + label + ")"
        return retString

    def vm_goto(label):
        '''Generate Hack Assembly code for a VM goto operation'''
        retString = "@" + label + "\n"
        retString += "0;JMP"
        return retString

    def vm_if(label):
        '''Generate Hack Assembly code for a VM if-goto operation'''
        retString = "@SP\n"
        retString += "AM = M-1\n"
        retString += "D = M\n"
        retString += "@" + label + "\n"
        retString += "D;JNE"

        return retString

    def vm_function(function_name, n_vars):
        '''Generate Hack Assembly code for a VM function operation'''
        retString = "(FUNC.defMod." + function_name + ")\n"
        retString += "@SP\n"
        retString += "A = M\n"
        for i in range(n_vars):
            retString += "M=0\n"
            retString += "A=A+1\n"
        retString += "D=A\n"
        retString += "@SP\n"
        retString += "M=D"

        return retString

    def vm_call(function_name, n_args):
        '''Generate Hack Assembly code for a VM call operation'''
        retString = "@SP\n"
        retString += "D=M\n"
        retString += "@R13\n"
        retString += "M=D\n"
        retString += "@SP\n"
        retString += "M=M+1\n"
        retString += "@LCL\n"
        retString += "D=M\n"
        retString += "@SP\n"
        retString += "A=M\n"
        retString += "M=D\n"
        retString += "@SP\n"
        retString += "M=M+1\n"
        retString += "@ARG\n"
        retString += "D=M\n"
        retString += "@SP\n"
        retString += "A=M\n"
        retString += "M=D\n"
        retString += "@SP\n"
        retString += "M=M+1\n"
        retString += "@R13\n"
        retString += "D=M\n"
        retString += "@" + function_name + "\n"
        retString += "0;JMP\n"
        retString += "(Ret." + function_name + ")"

        return retString

    def vm_return():
        '''Generate Hack Assembly code for a VM return operation'''
        return ""

# A quick-and-dirty parser when run as a standalone script.
if __name__ == "__main__":
    import sys
    if(len(sys.argv) > 1):
        with open(sys.argv[1], "r") as a_file:
            for line in a_file:
                tokens = line.strip().lower().split()
                if(len(tokens)==1):
                    if(tokens[0]=='add'):
                        print(VMTranslator.vm_add())
                    elif(tokens[0]=='sub'):
                        print(VMTranslator.vm_sub())
                    elif(tokens[0]=='neg'):
                        print(VMTranslator.vm_neg())
                    elif(tokens[0]=='eq'):
                        print(VMTranslator.vm_eq())
                    elif(tokens[0]=='gt'):
                        print(VMTranslator.vm_gt())
                    elif(tokens[0]=='lt'):
                        print(VMTranslator.vm_lt())
                    elif(tokens[0]=='and'):
                        print(VMTranslator.vm_and())
                    elif(tokens[0]=='or'):
                        print(VMTranslator.vm_or())
                    elif(tokens[0]=='not'):
                        print(VMTranslator.vm_not())
                    elif(tokens[0]=='return'):
                        print(VMTranslator.vm_return())
                elif(len(tokens)==2):
                    if(tokens[0]=='label'):
                        print(VMTranslator.vm_label(tokens[1]))
                    elif(tokens[0]=='goto'):
                        print(VMTranslator.vm_goto(tokens[1]))
                    elif(tokens[0]=='if-goto'):
                        print(VMTranslator.vm_if(tokens[1]))
                elif(len(tokens)==3):
                    if(tokens[0]=='push'):
                        print(VMTranslator.vm_push(tokens[1],int(tokens[2])))
                    elif(tokens[0]=='pop'):
                        print(VMTranslator.vm_pop(tokens[1],int(tokens[2])))
                    elif(tokens[0]=='function'):
                        print(VMTranslator.vm_function(tokens[1],int(tokens[2])))
                    elif(tokens[0]=='call'):
                        print(VMTranslator.vm_call(tokens[1],int(tokens[2])))

        