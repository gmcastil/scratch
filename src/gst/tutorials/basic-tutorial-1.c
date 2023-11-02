#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int tutorial_main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;

	/* Init GStreamer */
	gst_init(&argc, &argv);

	pipeline = gst_parse_launch(
			"playbin uri=http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/Sintel.mp4",
			NULL
			);

	/*
	 * Every GStreamer element has an associated state - for now, playback
	 * is not going to start until the pipeline has been set to PLAYING.
	 * Note that the element in this case is the `playbin` element, which is
	 * the only element in the pipeline. One can imagine that more
	 * sophisticated pipelines might have more elements that require their
	 * state to be set
	 */
	gst_element_set_state(pipeline, GST_STATE_PLAYING);

	/* Wait for an error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
			GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
	/* 
	 * The GStreamer bus will get explained in the next tutorial. Also, this
	 * last function appears to have had a side effect that created a `msg`
	 * that needed to be unreferenced.
	 */

	if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
		g_error("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
				"variable set for more details.");
	}

	/* Free resources, notice again that some of these were created by the
	 * process */
	gst_message_unref(msg);
	gst_object_unref(bus);
	/* This should free some more stuff too */
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

	return 0;
}

int main(int argc, char *argv[])
{
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
	return gst_macos_main(tutorial_main, argc, argv, NULL);
#else
	return tutorial_main(argc, argv);
#endif
}

	
