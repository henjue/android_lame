## [lame](http://lame.sourceforge.net/) for android  
[![dev](https://github.com/henjue/android_lame/actions/workflows/dev.yml/badge.svg)](https://github.com/henjue/android_lame/actions/workflows/dev.yml)
[![release](https://github.com/henjue/android_lame/actions/workflows/release.yml/badge.svg)](https://github.com/henjue/android_lame/actions/workflows/release.yml)
[![GitHub version](https://badge.fury.io/gh/henjue%2Fandroid_lame.svg)](https://badge.fury.io/gh/henjue%2Fandroid_lame)


# build.gradle
```gradle
dependencies {
       implementation 'com.github.henjue:android_lame:Tag'
}
```
## Kotlin Code
```kotlin
val mRecorder = com.github.henjue.lame.Mp3Recorder(file);
mRecorder.startRecording();
```
