import numpy as np

population = [10,20,30,40,50,60,70,80,90]

mean = np.mean(population)
median = np.median(population)
variance = np.var(population)

print(f"mean : {mean}\nMedian : {median}\nVariance : {variance: ,.2f}")