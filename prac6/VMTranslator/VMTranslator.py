class VMTranslator:

    def vm_push(segment, offset):
        '''Generate Hack Assembly code for a VM push operation'''
        string = "@" + offset + "\n" + "D = A\n@" + segment + "\n" + "A = A + D"

        return "" 

    def vm_pop(segment, offset):
        '''Generate Hack Assembly code for a VM pop operation'''
        return ""

    def vm_add():
        '''Generate Hack Assembly code for a VM add operation'''
        retString = "@SP\n"
        retString = "A = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "M = D + M\n"

        return retString

    def vm_sub():
        '''Generate Hack Assembly code for a VM sub operation'''
        retString = "@SP\n"
        retString = "A = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "M = M - D\n"

        return retString

    def vm_neg():
        '''Generate Hack Assembly code for a VM neg operation'''
        retString = "@SP\n"
        retString = "A = M-1\n"
        retString = "M = !M"
        retString = "M = M + 1"
        
        return retString

    def vm_eq():
        '''Generate Hack Assembly code for a VM eq operation'''
        retString = "@SP\n"
        retString = "AM = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "D = M - D\n"
        retString = "D;JEQ True\n"
        retString = "M = 0\n"
        retString = "(True)"
        retString = "M = -1"
        return retString

    def vm_gt():
        '''Generate Hack Assembly code for a VM gt operation'''
        '''Generate Hack Assembly code for a VM eq operation'''
        retString = "@SP\n"
        retString = "AM = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "D = M - D\n"
        retString = "D;JGT True\n"
        retString = "M = 0\n"
        retString = "(True)"
        retString = "M = -1"
        return retString

    def vm_lt():
        '''Generate Hack Assembly code for a VM lt operation'''
        '''Generate Hack Assembly code for a VM eq operation'''
        retString = "@SP\n"
        retString = "AM = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "D = M - D\n"
        retString = "D;JLT True\n"
        retString = "M = 0\n"
        retString = "(True)\n"
        retString = "M = -1\n"
        return retString

    def vm_and():
        '''Generate Hack Assembly code for a VM and operation'''
        retString = "@SP\n"
        retString = "AM = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "M = M&D\n"
        return retString

    def vm_or():
        '''Generate Hack Assembly code for a VM or operation'''
        retString = "@SP\n"
        retString = "AM = M-1\n"
        retString = "D = M"
        retString = "A = A-1\n"
        retString = "M = M|D\n"
        return retString

    def vm_not():
        '''Generate Hack Assembly code for a VM not operation'''
        '''Generate Hack Assembly code for a VM or operation'''
        retString = "@SP\n"
        retString = "A = M-1\n"
        retString = "M = !M"
        return retString

    def vm_label(label):
        '''Generate Hack Assembly code for a VM label operation'''
        retString = "(" + label + ")"
        return retString

    def vm_goto(label):
        '''Generate Hack Assembly code for a VM goto operation'''
        retString = "@" + label
        return retString

    def vm_if(label):
        '''Generate Hack Assembly code for a VM if-goto operation'''
        return ""

    def vm_function(function_name, n_vars):
        '''Generate Hack Assembly code for a VM function operation'''
        return ""

    def vm_call(function_name, n_args):
        '''Generate Hack Assembly code for a VM call operation'''
        return ""

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

        