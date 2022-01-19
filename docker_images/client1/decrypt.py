import sys
import base64

def algo(str, in1, in2):
    str2 = base64.b64decode(str)
    str3 = str2.decode('ascii')

    rail = [['\n' for i in range(len(str2))] for j in range(in2)]
    dd = None
    r, c = 0, 0

    for i in range(len(str3)):
        if r == 0:
            dd = True
        if r == in2 - 1:
            dd = False

        rail[r][c] = '*'
        c += 1

        if dd:
            r += 1
        else:
            r -= 1

    index = 0
    for i in range(in2):
        for j in range(len(str3)):
            if ((rail[i][j] == '*') and
               (index < len(str3))):
                rail[i][j] = str3[index]
                index += 1

    str4 = []
    r, c = 0, 0
    for i in range(len(str3)):
        if r == 0:
            dd = True
        if r == in2 - 1:
            dd = False

        if (rail[r][c] != '*'):
            str4.append(rail[r][c])
            c += 1

        if dd:
            r += 1
        else:
            r -= 1

    str4 = ''.join(str4)

    in1 = 26 - in1

    res = ''
    for i in range(len(str4)):
        c = str4[i]
        if c.isupper():
            res += chr((ord(c) + in1 - 65) % 26 + 65)
        elif c.islower():
            res += chr((ord(c) + in1 - 97) % 26 + 97)
        else:
            res += c

    return res


def decrypt(filename, in1, in2):
    with open(filename, 'rb') as i:
        input = i.read()
        in1 = int(in1)
        in2 = int(in2)
        res = algo(input, in1, in2);
        with open(filename[0:-4], 'w') as o:
            o.write(res)


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("python3 decrypt.py [FILE] [int1] [int2]\n")
    else:
        decrypt(sys.argv[1], sys.argv[2], sys.argv[3])
