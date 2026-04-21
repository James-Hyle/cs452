savedcmd_Hello.mod := printf '%s\n'   Hello.o | awk '!x[$$0]++ { print("./"$$0) }' > Hello.mod
