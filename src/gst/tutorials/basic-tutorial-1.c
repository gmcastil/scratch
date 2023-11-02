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

	/* Start playing */
	gst_element_set_state(pipeline, GST_STATE_PLAYING);

	/* Wait for an error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
			GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Check for an error */
	if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
		g_error("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
				"variable set for more details.");
	}

	/* Free resources */
	gst_message_unref(msg);
	gst_object_unref(bus);
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

	