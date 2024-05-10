# JSON grammar

```abnf
document = (value){1}

value = null | boolean | number | string | aggregate
null = "null"
boolean = "true" | "false"
number = (DIGIT)+ "."? (DIGIT)* 
string = "\"" NOT-QUOTE "\""

field = string ":" value

aggregate = array | object
array = "[" (value ("," value)*)? "]"
object = "{" (field ("," field)*)? "}"
```
