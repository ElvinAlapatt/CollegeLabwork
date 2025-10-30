import matplotlib.pyplot as plt

continents = ["asia","america","europe"]
areas = [12.7,10.4,9.5]

plt.figure(figsize=(10,6))
plt.bar(continents,areas,color = 'lightblue',edgecolor='black')
plt.title("Areas of continents")
plt.xlabel("continents")
plt.ylabel("Areas")

for i,area in enumerate(areas):
    plt.text(i,area + 0.2,str(area))

plt.tight_layout()
plt.show()