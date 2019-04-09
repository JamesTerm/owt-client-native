/*
 * Copyright � 2018 Intel Corporation. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OWT_BASE_AUDIOPLAYERINTERFACE_H_
#define OWT_BASE_AUDIOPLAYERINTERFACE_H_

#include <memory>

namespace owt {
namespace base {

/// PCM raw data and its information
struct PCMRawBuffer {
  /// PCM raw data
  int16_t* data;
  /// Bits per sample
  int bits_per_sample;
  /// Sample rate
  int sample_rate;
  /// Number of channels
  size_t number_of_channels;
  /// Number of samples per channel
  size_t number_of_frames;
  //TODO see why Chunbo deleted the data on the destructor
  ~PCMRawBuffer() { }
  //~PCMRawBuffer() { delete[] data; }
};

/// Interface for playing audio frames from an AudioTrack
class AudioPlayerInterface {
 public:
  /**
    @brief Destructor
  */
  virtual ~AudioPlayerInterface() {}

  /**
    @brief This function receives the PCM raw data and is designed for audio playout in most cases.
  */
  virtual void PlayAudio(std::unique_ptr<PCMRawBuffer> buffer) = 0;
};

}  // namespace base
}  // namespace owt

#endif // OWT_BASE_AUDIOPLAYERINTERFACE_H_
