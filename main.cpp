
//#include <stdio.h>
//#include <iostream>

//extern "C"{
//#include <libavformat/avformat.h>
//#include <libavutil/dict.h>
//}
//using namespace std;
//int main(int argc, char *argv[])
//{
//    AVFormatContext *fmt_ctx = NULL;

//    int ret;
//    char error[64];
//    string pathFile = "D:/FFMPEG/transformation/flip/build-flipVideo-Desktop_Qt_5_15_2_MinGW_32_bit-Release/release/test.mp4";

//    cout<<pathFile<<endl;
//    if ((ret = avformat_open_input(&fmt_ctx, pathFile.c_str(), NULL, NULL))){
//        cout<< av_make_error_string(error,64,ret)<<endl;
//        return ret;
//    }


//    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
//        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
//        return ret;
//    }
//    cout<<fmt_ctx->duration;
//    AVDictionaryEntry* metadataEntry = nullptr;
//    while ((metadataEntry = av_dict_get(fmt_ctx->metadata, "", metadataEntry, AV_DICT_IGNORE_SUFFIX))) {
//        std::cout << metadataEntry->key << ": " << metadataEntry->value << std::endl;
//    }
//    return 0;
//}
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

#include <iostream>

int main() {
    // Initialize FFmpeg
//    av_register_all();
//    avfilter_register_all();
//    avcodec_register_all();

    // Open input video file
    AVFormatContext *inputFormatContext = nullptr;
    if (avformat_open_input(&inputFormatContext, "D:/FFMPEG/transformation/flip/build-flipVideo-Desktop_Qt_5_15_2_MinGW_32_bit-Release/release/test.mp4", nullptr, nullptr) < 0) {
        std::cerr << "Could not open input file." << std::endl;
        return -1;
    }

    if (avformat_find_stream_info(inputFormatContext, nullptr) < 0) {
        std::cerr << "Failed to retrieve input stream information." << std::endl;
        return -1;
    }

    // Find the first video stream
    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < inputFormatContext->nb_streams; i++) {
        if (inputFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }
    if (videoStreamIndex == -1) {
        std::cerr << "Could not find video stream in the input file." << std::endl;
        return -1;
    }

    // Get the codec parameters and decoder
    AVCodecParameters *codecParameters = inputFormatContext->streams[videoStreamIndex]->codecpar;

    // Print stream information
    std::cout << "Video Stream Index: " << videoStreamIndex << std::endl;
    std::cout << "Codec ID: " << codecParameters->codec_id << std::endl;
    std::cout << "Width: " << codecParameters->width << std::endl;
    std::cout << "Height: " << codecParameters->height << std::endl;
    std::cout << "Pixel Format: " << codecParameters->format << std::endl;

    // Time base and aspect ratio
    AVRational timeBase = inputFormatContext->streams[videoStreamIndex]->time_base;
    AVRational aspectRatio = codecParameters->sample_aspect_ratio;

    std::cout << "Time Base: " << timeBase.num << "/" << timeBase.den << std::endl;
    std::cout << "Aspect Ratio: " << aspectRatio.num << "/" << aspectRatio.den << std::endl;



    AVCodec *decoder = const_cast<AVCodec *>(avcodec_find_decoder(codecParameters->codec_id));
    if (!decoder) {
        std::cerr << "Failed to find codec." << std::endl<<avcodec_get_name(codecParameters->codec_id)<<std::endl;
        return -1;
    }
    std::cout<<avcodec_get_name(codecParameters->codec_id)<<std::endl;
    std::cout<<decoder->long_name<<std::endl;

    // Initialize the codec context
    AVCodecContext *codecContext = avcodec_alloc_context3(decoder);
    if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
        std::cerr << "Failed to initialize codec context." << std::endl;
        return -1;
    }

    if (avcodec_open2(codecContext, decoder, nullptr) < 0) {
        std::cerr << "Failed to open codec." << std::endl;
        return -1;
    }
    // Print the codec context information
    std::cout << "Video Size: " << codecContext->width << "x" << codecContext->height << std::endl;
    std::cout << "Pixel Format: " << codecContext->pix_fmt << std::endl;
    std::cout << "Time Base: " << codecContext->time_base.num << "/" << codecContext->time_base.den << std::endl;
    std::cout << "Aspect Ratio: " << codecContext->sample_aspect_ratio.num << "/" << codecContext->sample_aspect_ratio.den << std::endl;


    // Initialize the filter graph
    AVFilterGraph *filterGraph = avfilter_graph_alloc();
    AVFilterContext *buffersrcCtx = nullptr;
    AVFilterContext *buffersinkCtx = nullptr;
    AVFilterContext *flipCtx = nullptr;

    // Create the buffer source filter
    AVFilter *buffersrc = const_cast<AVFilter *>(avfilter_get_by_name("buffer"));
    AVFilter *buffersink = const_cast<AVFilter *>(avfilter_get_by_name("buffersink"));
    AVFilter *flip = const_cast<AVFilter *>(avfilter_get_by_name("hflip"));  // Horizontal flip filter

    char args[512];
    snprintf(args, sizeof(args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             codecContext->width, codecContext->height, codecContext->pix_fmt,
             1/*codecContext->time_base.num*/, 30/*codecContext->time_base.den*/,
             codecContext->sample_aspect_ratio.num, codecContext->sample_aspect_ratio.den);


    // Create and initialize the source and sink filters
    if (avfilter_graph_create_filter(&buffersrcCtx, buffersrc, "in", args, nullptr, filterGraph) < 0) {
        std::cerr << "Failed to create buffer source filter." << std::endl;
        return -1;
    }

    if (avfilter_graph_create_filter(&buffersinkCtx, buffersink, "out", nullptr, nullptr, filterGraph) < 0) {
        std::cerr << "Failed to create buffer sink filter." << std::endl;
        return -1;
    }

    // Create and initialize the flip filter
    if (avfilter_graph_create_filter(&flipCtx, flip, "flip", nullptr, nullptr, filterGraph) < 0) {
        std::cerr << "Failed to create flip filter." << std::endl;
        return -1;
    }

    // Connect the filters
    if (avfilter_link(buffersrcCtx, 0, flipCtx, 0) < 0 || avfilter_link(flipCtx, 0, buffersinkCtx, 0) < 0) {
        std::cerr << "Failed to link filters." << std::endl;
        return -1;
    }

    // Configure the filter graph
    if (avfilter_graph_config(filterGraph, nullptr) < 0) {
        std::cerr << "Failed to configure filter graph." << std::endl;
        return -1;
    }

    // Read frames and apply the filter
    AVFrame *frame = av_frame_alloc();
    AVFrame *filteredFrame = av_frame_alloc();
    int response;

    while (av_read_frame(inputFormatContext, nullptr) >= 0) {
        if (avcodec_send_packet(codecContext, nullptr) < 0) {
            std::cerr << "Failed to send packet to decoder." << std::endl;
            break;
        }

        while (avcodec_receive_frame(codecContext, frame) >= 0) {
            if (av_buffersrc_add_frame(buffersrcCtx, frame) < 0) {
                std::cerr << "Failed to add frame to buffer source." << std::endl;
                break;
            }

            response = av_buffersink_get_frame(buffersinkCtx, filteredFrame);
            if (response >= 0) {
                // Process the filtered frame (e.g., write to output)
                std::cout << "Frame filtered and ready for further processing." << std::endl;
            } else if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                continue;
            } else {
                std::cerr << "Error during filtering." << std::endl;
                break;
            }

            av_frame_unref(filteredFrame);
        }

        av_frame_unref(frame);
    }

    // Cleanup
    av_frame_free(&frame);
    av_frame_free(&filteredFrame);
    avcodec_free_context(&codecContext);
    avfilter_graph_free(&filterGraph);
    avformat_close_input(&inputFormatContext);

    return 0;
}
