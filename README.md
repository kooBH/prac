# prac
practices

## Frequently Used

```python
import glob,os
import librosa
import numpy as np

import matplotlib.pyplot as plt   
import IPython.display as ipd

# force re-import
%load_ext autoreload
%autoreload 2

# display without display()
from IPython.core.interactiveshell import InteractiveShell
InteractiveShell.ast_node_interactivity = "all"

ipd.display(ipd.Markdown('## input'))
ipd.display(ipd.Audio(x, rate=sr))

plt.figure()
plt.plot(x)
plt.plot(y)
plt.title("Wav Plot")
plt.legend(["x","y"])

plt.figure()
plt.title("Specrogram")
plt.pcolormesh(torch.abs(Y).T, shading='flat') 

```
