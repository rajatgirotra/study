
class View:
    def __init__(self, **kwargs):
        for key, value in kwargs.iteritems():
            setattr(View, key, value)


if __name__ == "__main__":
    d = {'name': 'Rajat', 'age': 33, 'interest': 'c++'}
    v = View(**d)
    print v.age
    
