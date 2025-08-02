def add(num1, num2, base):
    ans = 0
    carry = 0
    power = 1

    while num1 > 0 or num2 > 0:
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

def multiply():
    return 0

def main():
    str = input()
    num1, num2, base = map(int, str.split())

    print(add(max(num1, num2), min(num1, num2), base))
    print(multiply())
    print(0)

if __name__ == "__main__":
    main()
