/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_MEDIA_CODEC_SERVICE_H
#define ANDROID_MEDIA_CODEC_SERVICE_H

#include <binder/BinderService.h>
#include <media/IMediaCodecService.h>
#include <media/stagefright/omx/OMX.h>
#include <media/stagefright/omx/OMXStore.h>

namespace android {

class MediaCodecService : public BinderService<MediaCodecService>,
        public BnMediaCodecService
{
    friend class BinderService<MediaCodecService>;    // for MediaCodecService()
public:
    MediaCodecService() : BnMediaCodecService() { }
    virtual ~MediaCodecService() { }
    virtual void onFirstRef() { }

    static const char*    getServiceName() { return "media.codec"; }

    virtual sp<IOMX>      getOMX();

    virtual sp<IOMXStore> getOMXStore();

    virtual status_t      onTransact(uint32_t code, const Parcel& data,
                                     Parcel* reply, uint32_t flags);

private:
    Mutex                 mOMXLock;
    sp<IOMX>              mOMX;
    Mutex                 mOMXStoreLock;
    sp<IOMXStore>         mOMXStore;
};

}   // namespace android

#endif  // ANDROID_MEDIA_CODEC_SERVICE_H
