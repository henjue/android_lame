package com.github.henjue.lame

import androidx.test.filters.SmallTest
import androidx.test.runner.AndroidJUnit4
import org.junit.runner.RunWith

@RunWith(AndroidJUnit4::class)
@SmallTest
class LameEncoderTest {
    fun getVersion(){
        LameEncoder.getVersion()
    }
}