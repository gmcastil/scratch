#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int tutorial_main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstElement *source;
	GstElement *filter;
	GstElement *convert;
	GstElement *sink;

	GstMessage *msg;
	GstStateChangeReturn ret;

	/* GStreamer creation */
	gst_init(&argc, &argv);

	source = gst_element_factory_make("videotestsrc", "source");
	filter = gst_element_factory_make("vertigotv", "filter");
	convert = gst_element_factory_make("videoconvert", "convert");
	sink = gst_element_factory_make("autovideosink", "sink");

	pipeline = gst_pipeline_new("test-pipeline");

	if (!pipeline || !source || !sink) {
		g_printerr("Not all elements could be created\n");
		return -1;
	}
	if (!filter || !convert) {
		g_printerr("Could not create filter element\n");
		return -1;
	}

	/*
	 * A pipeline is a particular type of bin (there are undoubtedly others)
	 * which is the element used to contain other elements
	 */
	gst_bin_add_many(GST_BIN(pipeline), source, filter, convert, sink, NULL);
	/*
	 * So it looks like the normal way to use this is to add the elements to
	 * the bin (which is a pipeline in our case) and then link them all
	 * together
	 */
	if (gst_element_link_many(source, filter, convert, sink, NULL) != TRUE) {
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	g_object_set(source, "pattern", 0, NULL);

	/* 
	 * Again, as in the previous example, changing the state to PLAYING is
	 * what begins to drag data through the pipeline
	 */
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	/*
	 * If there is a problem with changing the state to playing, this is
	 * going to get set.
	 */
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing\n");
		gst_object_unref(pipeline);
		return -1;
	}

	bus = gst_element_get_bus(pipeline);
	/* Wait until execution ends or there is an error or EOS */
	msg = gst_bus_timed_pop_filtered(
			bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS
			);

	/* And then do some error checking */
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

