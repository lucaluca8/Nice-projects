from random import randint


class Computers(object):
    def __init__(self):
        self.buffer = ""
        self.IP = self.generateIP()

    @classmethod
    def generateIP(self):
        IP=""
        list = []
        for i in range(4):
            num = randint(0,255)
            list.append(num)
        for i in list:
            if IP != "":
                IP+="."
            IP+=str(i)
        return IP
