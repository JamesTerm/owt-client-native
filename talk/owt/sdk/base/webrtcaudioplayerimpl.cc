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
#include "talk/owt/sdk/base/webrtcaudioplayerimpl.h"
#if defined(WEBRTC_WIN)
#include "talk/owt/sdk/base/win/d3dnativeframe.h"
#endif
#include "webrtc/media/base/videocommon.h"
namespace owt {
namespace base {
void WebrtcAudioPlayerImpl::OnData(const void* audio_data,int bits_per_sample,int sample_rate,size_t number_of_channels,size_t number_of_frames)
{
  //just wrap it and pass to the interface
  PCMRawBuffer pcm;
  pcm.bits_per_sample=bits_per_sample;
  pcm.data=(int16_t *)audio_data;
  pcm.number_of_channels=number_of_channels;
  pcm.number_of_frames=number_of_frames;
  pcm.sample_rate=sample_rate;
  m_player.PlayAudio(std::make_unique<PCMRawBuffer>(pcm));
}

}  // namespace base
}  // namespace owt
