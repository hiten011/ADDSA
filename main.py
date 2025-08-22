def add(num1, num2, base):
    ans = 0
    carry = 0
    power = 1

    while num1 > 0:
        n1 = num1 % 10
        n2 = num2 % 10

        num1 //= 10
        num2 //= 10

        total = n1 + n2 + carry

        carry = total // base
        curSum = total % base

        ans += curSum * power
        power *= 10

    ans += carry * power
    return ans

def helperMultiply(n, num, base):
    ans = 0
    for i in range(0,n):
        ans = add(min(ans, num), max(ans,num))
    return 0

def multiply(num1, num2, base):
    if num1 < 10 or num2 < 10:
        return helperMultiply(min(num1, num2), max(num1, num2), base)
    
    # length
    l = max(len(str(num1)), len(str(num2)))
    lh = l // 2

    # Split
    high1, low1 = divmod(num1, 10**lh)
    high2, low2 = divmod(num2, 10**lh)

    # recursive multiplications
    z0 = multiply(low1, low2)
    z1 = multiply((low1 + high1), (low2 + high2))
    z2 = multiply(high1, high2)

    # Combine results
    return z2 * 10**(2 * m) + (z1 - z2 - z0) * 10**m + z0


s = input()
num1, num2, base = map(int, s.split())
print(add(max(num1, num2), min(num1, num2), base), multiply(num1, num2, base), 0)
