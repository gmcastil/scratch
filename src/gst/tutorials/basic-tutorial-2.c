#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int tutorial_main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstElement *source;
	GstElement *sink;

	GstMessage *msg;
	GstStateChangeReturn ret;

	/* GStreamer creation */
	gst_init(&argc, &argv);

	source = gst_element_factory_make("videotestsrc", "source");
	sink = gst_element_factory_make("autovideosink", "sink");

	pipeline = gst_pipeline_new("test-pipeline");

	if (!pipeline || !source || !sink) {
		g_printerr("Not all elements could be created\n");
		return -1;
	}

	gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);
	if (gst_element_link(source, sink) != TRUE) {
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	g_object_set(source, "pattern", 0, NULL);

	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing\n");
		gst_object_unref(pipeline);
		return -1;
	}

	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(
			bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS
			);

	if (msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch (GST_MESSAGE_TYPE (msg)) {
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &debug_info);
				g_printerr("Error received rom element %s: %s\n",
						GST_OBJECT_NAME(msg->src), err->message);
				g_printerr("Debugging information: %s\n",
						debug_info ? debug_info : "none");
				g_clear_error(&err);
				g_free(debug_info);
				break;
			case GST_MESSAGE_EOS:
				g_print("End-Of-Stream reached.\n");
				break;
			default:
				/* We should not reach here because we only asked for ERRORs and EOS */
				g_printerr("Unexpected message received.\n");
				break;
		}
		gst_message_unref(msg);
	}

	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);

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

