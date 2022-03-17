import threading
from random import randint

import Computers
import Token

def tokenInitialize(computersList):
    list = computersList.copy()
    message = "Hey, I am the Token. Come and get me"
    isFree = True
    gotToDest = False
    pos = randint(0,len(list)-1)
    source = list[pos].IP
    list.pop(pos)
    pos = randint(0,len(list)-1)
    dest = list[pos].IP
    t = Token.Token(source,dest,message,isFree,gotToDest)
    print()
    print()
    print("Hello,I am the token and my soruce is "+ str(source)+ " and my destination is "+str(dest) )
    print()
    print()
    return t

def grabToken(computer,token):
    if computer.IP != token.source:
        if token.destination == computer.IP and token.reachedDest == False:
            print("I got to my destination: " + str(computer.IP))
            token.destination=token.source
            token.source=computer.IP
            token.reachedDest = True
        elif token.destination == computer.IP and token.reachedDest == True:
            print("I got back home: " + str(computer.IP))
            token.destination = ""
            token.source = ""
        else:
            print("Computer with the IP: " + str(computer.IP) + " tried to get the token")
    return token


def main():
    threads = []
    computersList = []
    for i in range(10):
        computer = Computers.Computers()
        computersList.append(computer)
    global t
    t=tokenInitialize(computersList)
    for c in computersList:
        thread=threading.Thread(target=grabToken,args=(c,t,))
        print("Creating and starting the computer with the IP: ",c.IP)
        threads.append(thread)
    print()
    print()
    for tr in threads:
        tr.start()
    for tr in threads:
        tr.join()
    if t.destination == "":
        newThreadList =[]
        for c in computersList:
            thread = threading.Thread(target=grabToken, args=(c, t,))
            newThreadList.append(thread)
        for tr in newThreadList:
            tr.start()
        for tr in newThreadList:
            tr.join()

if __name__ == "__main__":
    main()