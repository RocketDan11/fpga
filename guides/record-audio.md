#from terminal run this command
change hw to the right soundcard input
check inputs with 
```pactl list short sources```


```ffmpeg -f alsa -ac 1 -i plughw:4,0 -ar 44100 -c:a pcm\_s16le ~/intro1.wa```
