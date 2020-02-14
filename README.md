# mice

## grammer

**S** → if (**E**) **S** else **S**

&nbsp;&nbsp;&nbsp;&nbsp;| while (**E**) **S**

&nbsp;&nbsp;&nbsp;&nbsp;| { **L** }
  
&nbsp;&nbsp;&nbsp;&nbsp;| print **(E)**

**L** → **S** ; **L**

&nbsp;&nbsp;&nbsp;&nbsp;| ε

**E** → num = num

### example:

```
int i = 5;
while(i) {
  if(i == 3) {
    print('@');
  }
  i = i - 1;
}
```
