class field(object):
    figur = ''

    def __init__(self, fgr = 'empty'):
        self.figur = fgr

    def getFigur(self):
        return self.figur

    def setFigur(self, newfgr):
        self.figur = newfgr