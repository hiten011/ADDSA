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

def multiply(num1, num2):
    if num1 < 10 or num2 < 10:
        return num1 * num2

    n = max(len(str(num1)), len(str(num2)))
    m = n // 2

    # Split the digit sequences
    high1, low1 = divmod(num1, 10**m)
    high2, low2 = divmod(num2, 10**m)

    # recursive multiplications
    z0 = multiply(low1, low2)
    z1 = multiply((low1 + high1), (low2 + high2))
    z2 = multiply(high1, high2)

    # Combine results
    return z2 * 10**(2 * m) + (z1 - z2 - z0) * 10**m + z0

def to_base(num, base):
    ans = 0
    power = 1

    while num > 0:
        n = num % base
        num //= base

        curSum = n % base

        ans += curSum * power
        power *= 10

    return ans

def from_base(num, base):
    ans = 0
    idx = 0

    while num > 0:
        n = num % 10
        num //= 10

        ans += n * (base**idx)

        idx += 1

    return ans

s = input()
num1, num2, base = map(int, s.split())
print(add(max(num1, num2), min(num1, num2), base), to_base(multiply(from_base(num1, base), from_base(num2, base)), base), 0)
