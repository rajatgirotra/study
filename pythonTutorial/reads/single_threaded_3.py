import time

COUNT = 50000000  # 50 million


def countdown(n):
    while n > 0:
        --n


start = time.time()
countdown(COUNT)
end = time.time()
print('Time taken in seconds - %s' % (end-start))
