import factory

fun = factory.create("operation.add")
print(fun.__name__)
print(fun(1,2))
fun = factory.create("operation.minus")
print(fun.__name__)
print(fun(1,2))
fun = factory.create("operation.multify")
