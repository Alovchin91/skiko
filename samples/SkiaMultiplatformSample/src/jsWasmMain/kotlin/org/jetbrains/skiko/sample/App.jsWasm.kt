package org.jetbrains.skiko.sample

import kotlinx.browser.document
import org.jetbrains.skiko.*
import org.w3c.dom.HTMLCanvasElement

internal fun runApp() {
    val skiaLayer = SkiaLayer()
    onContentScaleChanged = { scale -> println(scale) }
    val game = JsClocks(skiaLayer)
    skiaLayer.skikoView = GenericSkikoView(skiaLayer, game)
    val canvas = document.getElementById("SkikoTarget") as HTMLCanvasElement
    canvas.setAttribute("tabindex", "0")
    skiaLayer.attachTo(canvas)
    skiaLayer.needRedraw()
}