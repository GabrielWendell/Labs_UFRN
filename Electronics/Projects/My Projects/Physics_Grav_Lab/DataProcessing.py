import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

# In[] Put Variables Here
# Theta in degress
theta = 23
# Gravity in m/s/s
g = 9.81
#change in position in m
x = 1.205
#margin of error
e = .95

# In[]



raw_data = np.load(r"Data\25deg.npy").reshape(-1).tolist()
data_list = []
for i in raw_data:
    if i >.05:
        data_list.append(i)
data_list = np.array(data_list).reshape(-1)

num_bins = 15
n, bins, patches = plt.hist(data_list, num_bins, density = 1, facecolor = 'Blue', alpha = 0.5)


def opt_plot():
    # plt.style.use('dark_background')
    plt.grid(True, linestyle=':', color='0.50')
    plt.minorticks_on()
    plt.tick_params(axis = 'both', which = 'minor', direction = "in",
                        top = True, right = True, length = 5, width = 1, labelsize = 15)
    plt.tick_params(axis = 'both', which = 'major', direction = "in",
                        top = True, right = True, length = 8, width = 1, labelsize = 15)

y = norm.pdf(bins, np.mean(data_list), np.std(data_list))
plt.plot(bins, y, 'r--', label = r'25$^{\circ}$')
plt.xlabel('Time in seconds')
plt.ylabel('Probability')
plt.title(r'Histogram of Times')
plt.legend(loc = 'best')
opt_plot()

# Tweak spacing to prevent clipping of ylabel
plt.subplots_adjust(left=0.15)
plt.show()

confidence = (norm.ppf(e))*(np.std(data_list)/np.sqrt(len(data_list)))



# In[]

print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
print("The average time was: "+str(np.mean(data_list)), "s")

final_awnser = (np.tan(np.radians(theta)))-((2*x)/(np.mean(data_list)*np.mean(data_list)*(g*np.cos(np.radians(theta)))))
print("The coefficent of friction for these results is: " + str(final_awnser))
print("The standard deviation of the times was: " + str(np.std(data_list)))
print("Margin of error with "+ str(e)[2:]+"% confidence: " + str(confidence))
print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")