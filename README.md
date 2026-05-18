# FH8862 RTSP 多视频流服务器

> 基于富瀚 FH8862 (ARM Cortex-A7) 的多路 RTSP 视频流服务器，支持 WebRTC 浏览器预览与远程控制。

[![平台](https://img.shields.io/badge/平台-FH8862%20ARM%20Cortex--A7-blue)](#)
[![RTSP](https://img.shields.io/badge/RTSP-live555-green)](#)
[![前端](https://img.shields.io/badge/前端-WebRTC%20%2B%20Node.js-orange)](#)

---



## 概述

本项目在 FH8862 嵌入式平台上实现了完整的 RTSP 视频推流管线：

| 环节 | 技术方案 |
|------|----------|
| 图像采集 | IMX415 MIPI CSI (4K 传感器) |
| 图像处理 | FH8862 ISP (自动曝光、白平衡、镜像翻转) |
| 视频编码 | 硬件 H.264 编码器 (双码流) |
| RTSP 服务 | **live555** C++ 库 |
| 流转发 | MediaMTX (RTSP → WebRTC/WHEP) |
| Web 前端 | HTML5 + WebRTC + Node.js 控制代理 |
| 板端控制 | TCP 控制服务 (端口 9999) |

**核心设计决策：**
- live555 库中的RTSP服务器，稳定通用
- 视频链路和控制链路分离：RTSP 负责推流，TCP 负责控制命令
- 一个网页便可同时预览和控制 4 路摄像头

---

## 系统架构

```
┌──────────────────┐    RTSP :8554     ┌──────────────────┐    WebRTC(WHEP)   ┌──────────────────┐
│                  │ ─────────────────→│                  │ ───────────────→  │                  │
│   FH8862 开发板   │                   │   Ubuntu 服务器  │                   │   浏览器 (PC)     │
│   192.168.1.3    │                   │   192.168.1.1    │                   │   :8080          │
│                  │                   │                  │                   │                  │
│  IMX415 → ISP    │  视频流推流        │  MediaMTX        │  视频流转发        │   2×2 视频墙      │
│  → H.264 编码    │ ────────────────→ │  (RTSP→WebRTC)   │ ───────────────→  │  主/子码流切换     │
│  → live555 RTSP  │                   │                  │                   │                  │
│                  │                   │                  │    HTTP API       │                  │
│                  │                   │  Node.js         │ ←───────────────  │    控制面板       │
│  控制服务 :9999   │ ←──TCP 控制指令 ──│  (HTTP→TCP 代理)  │                   │  OSD/Mask/LED    │
│                  │                   │                  │                   │  录像/时间同步    │
└──────────────────┘                   └──────────────────┘                   └──────────────────┘
```

### 多摄像头拓扑

```
路由器 (192.168.1.10)
  ├── 板1: 192.168.1.11   RTSP:8554  控制:9999
  ├── 板2: 192.168.1.12   RTSP:8554  控制:9999
  ├── 板3: 192.168.1.13   RTSP:8554  控制:9999
  ├── 板4: 192.168.1.14   RTSP:8554  控制:9999
  └── Ubuntu: 192.168.1.1  8080(Web)  8889(WebRTC)
```

---

## 目录结构

```
.
├── Makefile                    # 交叉编译 (arm-fullhanv3-)
├── make.sh                     # 编译 + 部署到 NFS
├── src/                        # 源代码
│   ├── main.c                  # 主入口，流管线
│   ├── isp.c                   # ISP 图像处理
│   ├── sensor.c                # I2C 传感器驱动
│   ├── control_server.c        # TCP 控制服务 (:9999)
│   ├── rtsp_live555.cpp        # live555 RTSP 服务模块
│   ├── h264_live_source.cpp    # H.264 帧源 (pull 模型)
│   ├── h264_subsession.cpp     # RTSP 子会话处理
│   ├── frame_queue.cpp         # 线程安全帧队列
│   └── libdmc*.c / libpes.c    # DMC 媒体框架 / PES (已弃用)
├── inc/                        # 内部头文件
│   └── rtsp_live555.h          # live555 C 兼容 API
├── include/                    # FH8862 SDK 头文件 (dsp, mpp, isp 等)
├── lib/
│   ├── static/                 # 静态库 (.a), Makefile 实际链接
│   ├── dynamic/                # 动态库 (.so) 备用
│   ├── live555/                # live555 预编译库 + 头文件
│   └── *.hex                   # IMX415 ISP 参数表
├── driver/                     # 内核模块 + 加载脚本
├── web/                        # Web 前端 + Node.js
│   ├── index.html              # 四路视频墙 + 控制面板
│   ├── css/ / js/              # 静态资源
│   ├── server.js               # HTTP API → TCP 控制代理
│   ├── mediamtx.yml            # MediaMTX 8路转发配置
│   ├── start.sh / stop.sh      # 启停脚本
│   └── mediamtx/               # MediaMTX 二进制
├── debug_汇总.md               # 完整调试记录
└── 项目总结.md                  # 本文件
```

---

## 快速开始
见使用方法.txt和运行指令.md


---

## 功能特性

### 视频墙
- 2×2 宫格同时展示 4 路摄像头
- 每路可独立切换主码流/子码流
- 默认全部子码流 (700kbps × 4 = 2.8Mbps)
<img src="https://github.com/Superbigbag/fh8862-multicam-rtsp-web/blob/main/image/%E5%A4%9A%E6%9C%BA%E4%BD%8D%E8%BF%90%E8%A1%8C2.jpg" width="400" alt="系统实物图">

### 远程web控制台
<img src="https://github.com/Superbigbag/fh8862-multicam-rtsp-web/blob/main/image/%E6%8E%A7%E5%88%B6%E5%8F%B0.png" width="400" alt="系统实物图">

| 功能 | 控件 | 说明 |
|------|------|------|
| 旋转 180° | 复选框 | ISP 镜像翻转 |
| OSD 文字 | 文本输入 | 支持 GB2312 中文叠加 |
| OSD 颜色 | RGB 滑块 | 每路独立调节 |
| OSD 反色 | 下拉选择 | 背景自适应反色 |
| 遮罩颜色 | RGB 滑块 | 隐私遮罩颜色 |
| 遮罩区域 | 坐标输入 | 最多 8 个可配置区域 |
| 设备端录像 | 秒数输入 | 板端存储录像文件 |
| PC 端录像 | 按钮 | 浏览器 MediaRecorder → WebM |
| LED 控制 | 按钮 | 灭 / 亮 / 闪烁 |
| 时间同步 | 按钮 | 广播系统时间到全部板子 |

### 控制架构

```
浏览器                      Node.js                     板端
  │                          │                          │
  │  POST /api/rotate        │                          │
  │  {camera_id:2, r:true}   │                          │
  ├─────────────────────────→│                          │
  │                          │  camera_id=2 → .1.12     │
  │                          │  TCP: "ROTATE 1\n"       │
  │                          ├─────────────────────────→│
  │                          │          "OK"            │
  │                          │←─────────────────────────┤
  │  {"ok":true}             │                          │
  │←─────────────────────────┤                          │
```

- 视频链路 (RTSP/WebRTC) 与控制链路 (HTTP/TCP) 完全分离
- 所有控制 API 携带 `camera_id` 字段，Node.js 据此路由到对应板端
- 时间同步并发广播到全部 4 块板

---

## 码流规格

| 码流 | 分辨率 | 码率 | RTSP 路径 | WebRTC 路径 |
|------|--------|------|-----------|-------------|
| 主码流 | 1280×720 | ~2 Mbps | `/main` | `camX_main` |
| 子码流 | 704×576 | ~700 kbps | `/sub` | `camX_sub` |

---

## 项目结果

### 板端推流中
<img src="https://github.com/Superbigbag/fh8862-multicam-rtsp-web/blob/main/image/%E5%A4%9A%E6%9C%BA%E4%BD%8D%E8%BF%90%E8%A1%8C1.jpg" width="300" alt="系统实物图">


### fh8862四机联调实物

<img src="https://github.com/Superbigbag/fh8862-multicam-rtsp-web/blob/main/image/%E5%9B%9B%E6%9C%BA%E4%BD%8D1.jpg" width="420" alt="系统实物图">
<img src="https://github.com/Superbigbag/fh8862-multicam-rtsp-web/blob/main/image/%E8%B7%AF%E7%94%B12.jpg" width="400" alt="系统实物图">

## 关键调试问题

### 1. Sensor MIPI 未就绪 → 编码器无帧

VLC 可连接无画面，日志 `API_ISP_Run error 0xa0084100`。Sensor 复位后 MIPI 锁相环建立需时间，ISP 提前取流导致管线失败。**修复:** `start_isp()` 中 `isp_server_run()` 前加 `usleep(500*1000)`。见 `src/main.c`。

### 2. I 帧超过 150KB 被 live555 StreamParser 截断 → 花屏

live555 `BANK_SIZE=150KB`，超限截断后 `fNumTruncatedBytes` 被 `afterGettingBytes1()` 忽略，新旧帧数据混叠致 NALU 错乱。**修复:** `h264_live_source.cpp` 改为分片交付。见 `src/h264_live_source.cpp`。

### 3. `includeStartCodeInOutput=True` 起始码干扰 FU-A → 主码流花屏

H264VideoStreamFramer 在每个 NALU 前加 `00 00 00 01`，H264VideoRTPSink FU-A 分片器预期纯 NALU，起始码 `0x00` 被误当 NALU header。**修复:** `includeStartCodeInOutput` 改为 `False`。见 `src/h264_subsession.cpp`。


### 4. 每帧 malloc/free → 长时间运行内存碎片化崩溃

双码流每秒 50 次 malloc/free (I帧可达 100KB+)，嵌入式 malloc 碎片化后大块分配失败。**缓解:** FrameQueue 降至 10、LED 线程泄漏已修补。



---

## 依赖项

### 板端
- 富瀚 FH8862 SDK (DSP, ISP, VPU, VENC, MPP 库)
- live555 (ARM 预编译静态库，位于 `lib/live555/`)
- 内核模块: vmm, xbus_rpc, media_process, vb, isp, vpu, enc, jpeg, bgm, nna, vgs, vou

### 服务器端 (Ubuntu)
- [MediaMTX](https://github.com/bluenviron/mediamtx) v1.11.3 (`start.sh` 中下载)
- Node.js + [iconv-lite](https://www.npmjs.com/package/iconv-lite) (中文字库 GB2312 编码转换)

### 浏览器
- 支持 WebRTC 的现代浏览器 (Chrome, Edge等)
