class AA(object):
    def __new__(cls):
        if not hasattr(cls,'instance'):
            print('create')
            cls.instance = super(AA, cls).__new__(cls)
        else:
            print('recycle')
        return cls.instance
    
    def set(self,val):
        self.val = val
        
    def get(self):
        return self.val