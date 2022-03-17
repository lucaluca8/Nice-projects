class Token:
    def __init__(self, source, destination, message, isFree, reachedDest):
        self.source = source
        self.destination = destination
        self.message = message
        self.isFree = isFree
        self.reachedDest = reachedDest
