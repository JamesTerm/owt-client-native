// Copyright (C) <2018> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0
#if defined(WEBRTC_WIN)
#include <Windows.h>
#include <atlbase.h>
#include <codecapi.h>
#include <combaseapi.h>
#include <d3d9.h>
#include <dxva2api.h>
#endif
#include "talk/owt/sdk/base/webrtcvideorendererimpl.h"
#if defined(WEBRTC_WIN)
#include "talk/owt/sdk/base/win/d3dnativeframe.h"
#endif
#include "webrtc/common_video/libyuv/include/webrtc_libyuv.h"
#include "webrtc/media/base/videocommon.h"

//TODO this is only for development, if we need to use it then we'll need to implement properly
#define __JamesHack__
#ifdef __JamesHack__
namespace webrtc
{
  extern std::function<const char*(int,const char**)> g_VideoReceiveStream_SetOptions;
}
#endif

namespace owt {
namespace base {
void WebrtcVideoRendererImpl::OnFrame(const webrtc::VideoFrame& frame) 
{
  CheckOptions();
  const VideoRendererType renderer_type = renderer_.Type();
  if (frame.video_frame_buffer()->type() == webrtc::VideoFrameBuffer::Type::kNative) 
  {
    //Make sure we are asking for these
    if (renderer_type!=VideoRendererType::kNative)
      return;
    //Note: we should make a render_type check, but since this is hard configured
    //It is not necessary
    using namespace webrtc;
    const rtc::scoped_refptr<VideoFrameBuffer> video_frame_buffer=frame.video_frame_buffer();
    const INativeBufferInterface* frame_info=video_frame_buffer->GetINative();
    //Note we must address the compressed frame size directly
    const size_t frame_size=frame_info->size();
    uint8_t* buffer = new uint8_t[frame_size];
    Resolution resolution(frame.width(), frame.height());
    memcpy(buffer,frame_info->Data(),frame_size);
    std::unique_ptr<VideoBuffer> video_buffer(new VideoBuffer{buffer, resolution, VideoBufferType::kNative});
    renderer_.RenderFrame(std::move(video_buffer));
    return;
  }
  if (renderer_type != VideoRendererType::kI420 && renderer_type != VideoRendererType::kARGB)
    return;
  Resolution resolution(frame.width(), frame.height());
  if (renderer_type == VideoRendererType::kARGB) 
  {
    uint8_t* buffer = new uint8_t[resolution.width * resolution.height * 4];
    webrtc::ConvertFromI420(frame, webrtc::VideoType::kARGB, 0, static_cast<uint8_t*>(buffer));
    std::unique_ptr<VideoBuffer> video_buffer(new VideoBuffer{buffer, resolution, VideoBufferType::kARGB});
    renderer_.RenderFrame(std::move(video_buffer));
  } 
  else 
  {
    uint8_t* buffer = new uint8_t[resolution.width * resolution.height * 3 / 2];
    webrtc::ConvertFromI420(frame, webrtc::VideoType::kI420, 0,static_cast<uint8_t*>(buffer));
    std::unique_ptr<VideoBuffer> video_buffer(new VideoBuffer{buffer, resolution, VideoBufferType::kI420});
    renderer_.RenderFrame(std::move(video_buffer));
  }
}

  void WebrtcVideoRendererImpl::CheckOptions()
  {
    //Poll for callback until we have it... we should get it on the first try
    if (!video_options_callback_)
    {
      #ifdef __JamesHack__
      if (webrtc::g_VideoReceiveStream_SetOptions)
      {
        SetVideoOptionsCallback(webrtc::g_VideoReceiveStream_SetOptions);
        //cache an initial read of the value
        const char* args[] ={"get_want_h264_frames"};
        const char* result=video_options_callback_(1,args);
        want_h264_frames_=strcmp(result,"true")==0?true:false;
      }
      else
        return;
      #else
        return;
      #endif
    }
    bool renderer_wants=renderer_.Type()==VideoRendererType::kNative?true:false;
    if (want_h264_frames_!=renderer_wants)
    {
      //Change to current settings
       const char* set_value=renderer_wants?"true":"false";
       const char* set_args[] ={"set_want_h264_frames",set_value};
      video_options_callback_(2,set_args);

      //this is redundant but let's be sure it took
      const char* args[] ={"get_want_h264_frames"};
      const char* result=video_options_callback_(1,args);
      want_h264_frames_=strcmp(result,"true")==0?true:false;
      printf("* _want_h264_frames=%s",result);
    }
  }

  void WebrtcVideoRendererImpl::SetVideoOptionsCallback(std::function<const char*(int,const char**)> video_options_callback)
  {
    video_options_callback_ = video_options_callback;
  }


}  // namespace base
}  // namespace owt
