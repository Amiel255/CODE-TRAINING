# 1. Factorial of n
def factorial(n):
    if n == 0 or n == 1:
        return 1

    return n * factorial(n - 1)


# 2. Print numbers from 1 to n
def printn(n):
    if n <= 0:
        return

    printn(n - 1)
    print(n)


# 3. Sum of array elements
def sumA(arr, i=0):
    if i == len(arr):
        return 0

    return arr[i] + sumA(arr, i + 1)


# 4. Largest element in an array
def largest_element(arr, i=0):
    if i == len(arr) - 1:
        return arr[i]

    rest_max = largest_element(arr, i + 1)

    return arr[i] if arr[i] > rest_max else rest_max


# 5. Count number of digits
def countdigits(n):
    n = abs(n)

    if n < 10:
        return 1

    return 1 + countdigits(n // 10)


# 6. Sum of digits
def sumofdigits(n):
    n = abs(n)
    if n < 10:
        return n
    return n % 10 + sumofdigits(n // 10)


# 7. Check if array is sorted
def isSorted(arr, i=0):
    if i >= len(arr) - 1:
        return True

    if arr[i] > arr[i + 1]:
        return False

    return isSorted(arr, i + 1)


# 8. Palindrome number
def isPalindromenum(n):
    s = str(abs(n))

    def check(s, left, right):
        if left >= right:
            return True

        if s[left] != s[right]:
            return False

        return check(s, left + 1, right - 1)

    return check(s, 0, len(s) - 1)


# 9. Palindrome array
def isPalindromearr(arr, left=0, right=None):
    if right is None:
        right = len(arr) - 1

    if left >= right:
        return True

    if arr[left] != arr[right]:
        return False

    return isPalindromearr(arr, left + 1, right - 1)


# 10. Greatest Common Divisor
def gcd(a, b):
    if b == 0:
        return a

    return gcd(b, a % b)


# 11. Check if prime number
def isPrime(n, divisor=2):
    if n < 2:
        return False

    if divisor * divisor > n:
        return True

    if n % divisor == 0:
        return False
    
    return isPrime(n, divisor + 1)
    
    
