import sys
import base64

def algo(str, in1, in2):
    str2 = ''
    for i in range(len(str)):
        c = str[i]
        if c.isupper():
            str2 += chr((ord(c) + in1 - 65) % 26 + 65)
        elif c.islower():
            str2 += chr((ord(c) + in1 - 97) % 26 + 97)
        else:
            str2 += c

    rail = [[None for i in range(len(str2))] for j in range(in2)]
    dd = False
    r, c = 0, 0
    for i in range(len(str2)):
        if (r == 0) or (r == in2-1):
            dd = not dd
        rail[r][c] = str2[i]
        c += 1

        if dd:
            r += 1
        else:
            r -= 1;
    str3 = []
    for i in range(in2):
        for j in range(len(str2)):
            if rail[i][j] is not None:
                str3.append(rail[i][j])
    str3 = ''.join(str3)

    str4 = str3.encode('ascii')
    res = base64.b64encode(str4)
    return res


def encrypt(filename, in1, in2):
    with open(filename, 'r') as i:
        input = i.read()
        in1 = int(in1)
        in2 = int(in2)
        res = algo(input, in1, in2);
        with open(filename+'.enc', 'wb') as o:
            o.write(res)


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("python3 encrypt.py [FILE] [int1] [int2]\n")
    else:
        encrypt(sys.argv[1], sys.argv[2], sys.argv[3])
