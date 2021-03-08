import importlib

def create(cls):
    '''expects a string that can be imported as with a module.class name'''
    module_name, class_name = cls.rsplit(".",1)

    try:
        module = importlib.import_module(module_name)
        instance = getattr(module, class_name)
    except Exception as err:
        raise AttributeError("Error: {0}".format(err))

    return instance
