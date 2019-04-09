
#ifndef OWT_BASE_WEBRTCAUDIOPLAYERIMPL_H_
#define OWT_BASE_WEBRTCAUDIOPLAYERIMPL_H_
#include "webrtc/api/mediastreaminterface.h"
#include "talk/owt/sdk/include/cpp/owt/base/audioplayerinterface.h"
namespace owt {
namespace base {
class WebrtcAudioPlayerImpl : public webrtc::AudioTrackSinkInterface 
{
public:
    WebrtcAudioPlayerImpl(AudioPlayerInterface& player) : m_player(player) 
    {}
    virtual void OnData(const void* audio_data,int bits_per_sample,int sample_rate,size_t number_of_channels,size_t number_of_frames);
    virtual ~WebrtcAudioPlayerImpl() {}
private:
    AudioPlayerInterface &m_player;
};

}
}
#endif  // OWT_BASE_AUDIOPLAYERIMPL_H_
