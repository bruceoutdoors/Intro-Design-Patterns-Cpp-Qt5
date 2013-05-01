Phonon on Windows does not have good MP3 metadata support,
even if you install all of the optional codecs. 
Some versions of windows need extra codecs to be installed.
Try googling for "k-lite codec pack full" to get extra codecs.

On linux, you need your backend to have a good mp3 decoder.
If you are using gstreamer as the backend,
be sure to install the gstreamer-fluendo mp3 codec plugin
