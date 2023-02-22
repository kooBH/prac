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


ipd.display(ipd.Markdown('## input'))
ipd.display(ipd.Audio(x, rate=sr))

plt.figure()
plt.plot(x)
plt.title("x")
```
