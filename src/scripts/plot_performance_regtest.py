import matplotlib.pyplot as plt
import numpy as np
from performance_regtest_results import *

objects = ("Alloc", "Scan")
values = [alloc_regtest, scan_regtest]
y_pos = np.arange(len(objects))

plt.bar(y_pos, values, align="center")
plt.xticks(y_pos, objects)
plt.ylabel("Time (s)")
plt.title(" Execution time of Buffer Pool operations")
plt.show()
