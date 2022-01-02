#ifndef _MAX98357_H_
#define _MAX98357_H_

#define I2S_DOUT     25
#define I2S_BCLK     27
#define I2S_LRC      26
#define MAX_CHANNEL  17

const char max98357_channel[MAX_CHANNEL][100] = {"https://str.vov.gov.vn/vovlive/vov1vov5Vietnamese.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov2.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov247vov5English.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov3.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov4.DBCuuLong.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov4.HCM.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov4.MienTrung.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov4.TayBac.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov4.TayNguyen.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov5.JapaneseIndonesia.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov5.RussianChinese.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov5.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov5.SpanishGermanFrench.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vov5.ThaiLaotianKhmer.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vovFM89.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vovGTHCM.sdp_aac/playlist.m3u8", \
                                 "https://str.vov.gov.vn/vovlive/vovGTHN.sdp_aac/playlist.m3u8"};

typedef enum
{
  max98357_success = 0,
  max98357_failed
} max98357_status;

max98357_status max98357_wifi_init(void);

void max98357_init(const char add[]);

void max98357_play(void);

void max98357_stop(void);

void max98357_setVolume(uint8_t value);

#endif /* _MAX98357_H_ */
