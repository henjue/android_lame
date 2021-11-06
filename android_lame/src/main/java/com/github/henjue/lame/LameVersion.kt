package com.github.henjue.lame

import androidx.annotation.Keep

@Keep

data class LameVersion constructor (
    var major: Int = 0,
    var minor: Int = 0,
    var alpha: Boolean = false,
    var beta: Boolean = false,
    var psy_major: Int = 0,
    var psy_minor: Int = 0,
    var psy_alpha: Boolean = false,
    var psy_beta: Boolean = false,
    var features: String = "",
)