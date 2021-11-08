package org.jetbrains.skiko

import org.jetbrains.skiko.redrawer.*

internal interface RenderFactory {
    fun createRedrawer(layer: SkiaLayer, renderApi: GraphicsApi, properties: SkiaLayerProperties): Redrawer

    companion object {
        val Default = makeDefaultRenderFactory()
    }
}

private fun makeDefaultRenderFactory(): RenderFactory {
    return object : RenderFactory {
        override fun createRedrawer(
            layer: SkiaLayer,
            renderApi: GraphicsApi,
            properties: SkiaLayerProperties
        ): Redrawer = when (hostOs) {
            OS.MacOS -> when (renderApi) {
                GraphicsApi.SOFTWARE_COMPAT, GraphicsApi.SOFTWARE_FAST -> SoftwareRedrawer(layer, properties)
                else -> MetalRedrawer(layer, properties)
            }
            OS.Windows -> when (renderApi) {
                GraphicsApi.SOFTWARE_COMPAT -> SoftwareRedrawer(layer, properties)
                GraphicsApi.SOFTWARE_FAST -> WindowsSoftwareRedrawer(layer, properties)
                GraphicsApi.OPENGL -> WindowsOpenGLRedrawer(layer, properties)
                else -> Direct3DRedrawer(layer, properties)
            }
            OS.Linux -> when (renderApi) {
                GraphicsApi.SOFTWARE_COMPAT -> SoftwareRedrawer(layer, properties)
                GraphicsApi.SOFTWARE_FAST -> LinuxSoftwareRedrawer(layer, properties)
                else -> LinuxOpenGLRedrawer(layer, properties)
            }
            OS.JS, OS.Ios -> {
                TODO("Commonize me")
            }
        }
    }
}