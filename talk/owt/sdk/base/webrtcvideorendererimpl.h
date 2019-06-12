// Copyright (C) <2018> Intel Corporation
//
// SPDX-License-Identifier: Apache-2.0
#ifndef OWT_BASE_WEBRTCVIDEORENDERERIMPL_H_
#define OWT_BASE_WEBRTCVIDEORENDERERIMPL_H_
#include "webrtc/api/mediastreaminterface.h"
#include "webrtc/api/video/video_sink_interface.h"
#include "webrtc/api/video/video_frame.h"
#include "talk/owt/sdk/include/cpp/owt/base/videorendererinterface.h"
namespace owt {
namespace base {
class WebrtcVideoRendererImpl
    : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
 public:
  WebrtcVideoRendererImpl(VideoRendererInterface& renderer)
      : renderer_(renderer) {}
  virtual void OnFrame(const webrtc::VideoFrame& frame) override;
  virtual ~WebrtcVideoRendererImpl() {}

  void SetVideoOptionsCallback(std::function<const char*(int,const char**)> video_options_callback);
 private:
  VideoRendererInterface& renderer_;

  void CheckOptions();
  std::function<const char*(int,const char**)> video_options_callback_=nullptr;  //provide callback to set video options
  bool want_h264_frames_=false;  //cache last state of this option
};
}
}
#endif  // OWT_BASE_VIDEORENDERERIMPL_H_
