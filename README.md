[build instructions](https://wiki.xwax.org/build_xwax_from_source)
[rtprio](https://wiki.xwax.org/setting_up_real_time_audio_priority_for_xwax)

```
sudo apt install build-essential libasound2-dev libasound2 libsdl-ttf2.0-dev libsdl1.2-dev
sudo apt-get install cdparanoia mpg123 ffmpeg

./configure --prefix /usr --enable-alsa

```
```
./xwax -s scan -i import -t mixvibes_v2 -l /media/toni/data/music/ -a deck1 
```
----------------------------
xwax: Digital vinyl on Linux

(C) Copyright 2021 Mark Hills <mark@xwax.org>

For installation instructions, see the INSTALL file. Instructions can
be found in the xwax(1) man page and http://xwax.org/

"xwax" is a digital vinyl system (DVS) for Linux. It allows DJs and
turntablists to playback digital audio files (MP3, Ogg Vorbis, FLAC,
AAC and more), controlled using a normal pair of turntables via
timecoded vinyls.

"xwax" is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License, version 3 as
published by the Free Software Foundation.

"xwax" is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <https://www.gnu.org/licenses/>.
