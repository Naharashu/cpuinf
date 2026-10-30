#include <FL/Enumerations.H>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tabs.H>
#include <chrono>
#include <cpuid.h>
#include <cpuinfo.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/utsname.h>
#include <thread>
#include <FL/Fl_Image.H>
#include "./intel.xpm"
#include "./amd.xpm"
#include "./logo.xpm"
#include "./x86.xpm"
#include "./arm.xpm"


std::string get_features() {
    #if defined(__x86_64__) || defined (__i386__)
        struct utsname buffer;
        uname(&buffer);
        std::string features = std::string(buffer.machine) == "x86_64" ? "x86_64" : "x86";

        if (cpuinfo_has_x86_fpu())
            features += ", x87";
        if (cpuinfo_has_x86_mmx())
            features += ", MMX";
        if (cpuinfo_has_x86_sse())
            features += ", SSE1";
        if (cpuinfo_has_x86_sse2())
            features += ", SSE2";
        if (cpuinfo_has_x86_sse3())
            features += ", SSE3";
        if (cpuinfo_has_x86_ssse3())
            features += ", SSSE3";
        if (cpuinfo_has_x86_sse4_1())
            features += ", SSE4.1";
        if (cpuinfo_has_x86_sse4_2())
            features += ", SSE4.2";
        if (cpuinfo_has_x86_aes())
            features += ", AES-NI";
        if (cpuinfo_has_x86_sha())
            features += ", SHA-NI";
        if (cpuinfo_has_x86_avx())
            features += ", AVX";
        if (cpuinfo_has_x86_avx2())
            features += ", AVX2";
        if (cpuinfo_has_x86_avx512f() && cpuinfo_has_x86_avx512bw() && cpuinfo_has_x86_avx512dq() &&
            cpuinfo_has_x86_avx512cd() && cpuinfo_has_x86_avx512vl())
            features += ", AVX512(F, BW, DQ, CD, VL)";
        if (cpuinfo_has_x86_avx10_1())
            features += ", AVX10.1";
        if (cpuinfo_has_x86_avx10_2())
            features += ", AVX10.2";
        if (cpuinfo_has_x86_popcnt())
            features += ", POPCNT";
        if (cpuinfo_has_x86_lzcnt())
            features += ", LZCNT";
        if (cpuinfo_has_x86_bmi())
            features += ", BMI1";
        if (cpuinfo_has_x86_bmi2())
            features += ", BMI2";
        if (cpuinfo_has_x86_fma3())
            features += ", FMA3";
        if (cpuinfo_has_x86_fma4())
            features += ", FMA4";
        if (cpuinfo_has_x86_f16c())
            features += ", F16C";

        std::ifstream f("/proc/cpuinfo");
        std::string line;

        while(std::getline(f, line)) {
            if(line.contains(" vmx ")) {
                features += ", Intel VT-X";
                break;
            }
            if(line.contains(" svm ")) {
                features += ", AMD-V";
                break;
            }
        }

        f.close();
    #elif defined(__aarch64__) || defined(__arm__)
        struct utsname buffer;
        uname(&buffer);
        std::string features = std::string(buffer.machine) == "aarch64" ? "aarch64" : "arm";

        if(cpuinfo_has_arm_neon()) features += ", NEON";
        if(cpuinfo_has_arm_vfpv2()) features += ", VFPv2";
        if(cpuinfo_has_arm_vfpv3()) features += ", VFPv3";
        if(cpuinfo_has_arm_vfpv4()) features += ", VFPv4";
        if(cpuinfo_has_arm_aes()) features += ", AES";
        if(cpuinfo_has_arm_sha1()) features += ", SHA1";
        if(cpuinfo_has_arm_sha2()) features += ", SHA2";
        if(cpuinfo_has_arm_crc32()) features += ", CRC32";

        if(cpuinfo_has_arm_sve()) features += ", SVE";
        if(cpuinfo_has_arm_sve2()) features += ", SVE2";
        if(cpuinfo_has_arm_bf16()) features += ", BFloat16";
        if(cpuinfo_has_arm_i8mm()) features += ", Int8-MatMul";
    #endif

    return features;
}

std::string uarch_name() {
    const struct cpuinfo_core* core = cpuinfo_get_core(0);

    if(core->uarch==cpuinfo_uarch_sky_lake||core->uarch==cpuinfo_uarch_kaby_lake) return "Skylake/Kaby Lake/Coffee Lake/Comet Lake";
    switch(core->uarch) {
        case cpuinfo_uarch_conroe: {
            return "conroe";
        }
        case cpuinfo_uarch_penryn: {
            return "penryn";
        }
        case cpuinfo_uarch_nehalem: {
            return "nehalem/westmere";
        }
        case cpuinfo_uarch_sandy_bridge: {
            return "sandy bridge";
        }
        case cpuinfo_uarch_ivy_bridge: {
            return "ivy bridge";
        }
        case cpuinfo_uarch_bulldozer: {
            return "bulldozer";
        }
        case cpuinfo_uarch_haswell: {
            return "haswell";
        }
        case cpuinfo_uarch_broadwell: {
            return "broadwell";
        }
        case cpuinfo_uarch_sunny_cove: {
            return "Sunny cove";
        }
        case cpuinfo_uarch_willow_cove: {
            return "Willow cove";
        }
        case cpuinfo_uarch_golden_cove: {
            return "Golden cove";
        }
        case cpuinfo_uarch_raptor_cove: {
            return "Raptor cove";
        }
        case cpuinfo_uarch_redwood_cove: {
            return "Redwood cove";
        }
        case cpuinfo_uarch_excavator: {
            return "excavator";
        }
        case cpuinfo_uarch_steamroller: {
            return "steamroller";
        }
        case cpuinfo_uarch_piledriver: {
            return "piledriver";
        }
        case cpuinfo_uarch_zen: {
            return "zen/zen+";
        }
        case cpuinfo_uarch_zen2: {
            return "zen2";
        }
        case cpuinfo_uarch_zen3: {
            return "zen3";
        }
        case cpuinfo_uarch_zen4: {
            return "zen4";
        }
        case cpuinfo_uarch_zen5: {
            return "zen5";
        }
        case cpuinfo_uarch_zen6: {
            return "zen6";
        }
        case cpuinfo_uarch_k10: {
            return "K10";
        }
        case cpuinfo_uarch_k8: {
            return "K8";
        }
        case cpuinfo_uarch_jaguar: {
            return "Jaguar";
        }
        case cpuinfo_uarch_goldmont: {
            return "Goldmont (Apollo Lake)";
        }
        case cpuinfo_uarch_goldmont_plus: {
            return "Goldmont+ (Gemini Lake)";
        }
        case cpuinfo_uarch_k7: {
            return "K7";
        }
        case cpuinfo_uarch_p6: {
            return "P6";
        }
        case cpuinfo_uarch_crestmont: {
            return "Crestmont (Meteor Lake)";
        }
        case cpuinfo_uarch_darkmont: {
            return "Darkmont";
        }
        case cpuinfo_uarch_gracemont: {
            return "Gracemont";
        }
        case cpuinfo_uarch_prescott: {
            return "Prescott";
        }
        case cpuinfo_uarch_cortex_a57: {
            return "Cortex-A57";
        }
        case cpuinfo_uarch_cortex_a53: {
            return "Cortex-A53";
        }
        case cpuinfo_uarch_cortex_a55: {
            return "Cortex-A55";
        }
        case cpuinfo_uarch_cortex_a32: {
            return "Cortex-A32";
        }
        case cpuinfo_uarch_cortex_a72: {
            return "Cortex-A72";
        }
        case cpuinfo_uarch_cortex_a73: {
            return "Cortex-A73";
        }
        case cpuinfo_uarch_cortex_a75: {
            return "Cortex-A75";
        }
        case cpuinfo_uarch_cortex_a76: {
            return "Cortex-A76";
        }
        case cpuinfo_uarch_cortex_a77: {
            return "Cortex-A77";
        }
        case cpuinfo_uarch_cortex_a78: {
            return "Cortex-A78";
        }
        case cpuinfo_uarch_cortex_x1: {
            return "Cortex-X1";
        }
        case cpuinfo_uarch_cortex_x2: {
            return "Cortex-X2";
        }
        case cpuinfo_uarch_cortex_x3: {
            return "Cortex-X3";
        }
        case cpuinfo_uarch_cortex_x4: {
            return "Cortex-X4";
        }
        case cpuinfo_uarch_cortex_x925: {
            return "Cortex-X925";
        }
        case cpuinfo_uarch_arm7: {
            return "ARM7";
        }
        case cpuinfo_uarch_hurricane: {
            return "Apple Hurricane (A10)";
        }
        case cpuinfo_uarch_monsoon: {
            return "Apple Monsoon (A11)";
        }
        case cpuinfo_uarch_vortex: {
            return "Apple Vortex (A12)";
        }
        case cpuinfo_uarch_lightning: {
            return "Apple Lightning (A13)";
        }
        case cpuinfo_uarch_firestorm: {
            return "Apple Firestorm (A14/M1)";
        }
        case cpuinfo_uarch_avalanche: {
            return "Apple Avalanche (A15/M2)";
        }
        case cpuinfo_uarch_kryo: {
            return "Qualcomm Kryo";
        }
        case cpuinfo_uarch_krait: {
            return "Qualcomm Krait";
        }
        case cpuinfo_uarch_exynos_m1: {
            return "Samsung Mongoose M1";
        }
        case cpuinfo_uarch_exynos_m2: {
            return "Samsung Mongoose M2";
        }
        case cpuinfo_uarch_exynos_m3: {
            return "Samsung Meerkat M3";
        }
        case cpuinfo_uarch_exynos_m4: {
            return "Samsung Mongoose M4";
        }
        case cpuinfo_uarch_exynos_m5: {
            return "Samsung Mongoose M5";
        }
        default: {
            char b[32];
            snprintf(b, sizeof b, "Unknown (0x%08x)", (unsigned)core->uarch);
            return b;
        }
    }
}

Fl_Box *text = nullptr;
Fl_Box *image_box = nullptr;
Fl_Pixmap* logo = nullptr;
Fl_Box *about = nullptr;
void info(void* data) {
    const struct cpuinfo_package *cpu = cpuinfo_get_package(0);
    std::string Name = cpu->name;
    std::string Vendor;

    if (Name.contains("Intel")) {
        Vendor = "Intel";
    }
    else if (Name.contains("AMD")) {
        Vendor = "AMD";
    }
    else
        Vendor = "Unknown";

    long MinFreq = 0;
    long MaxFreq = 0;
    long CurrFreq = 0;
    std::ifstream f("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq");
    f >> MinFreq;
    f.close();

    f.open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
    f >> MaxFreq;
    f.close();

    f.open("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
    f >> CurrFreq;
    f.close();

    std::ostringstream buf;
    buf << "Vendor: " << Vendor << '\n'
        << "Name: " << Name << '\n'
        << "Microarchitecture name: " << uarch_name() << '\n'
        << "Min freq: " << MinFreq / 1000 << " MHz" << '\n'
        << "Max freq: " << MaxFreq / 1000 << " MHz" << '\n'
        << "Current freq: " << CurrFreq / 1000 << " MHz" << '\n'
        << "Cores: " << cpuinfo_get_cores_count() << '\n'
        << "Threads: " << cpu->processor_count 
        << "\n────────────────────────────\n"
        << "L1 cache(per core): " << (cpuinfo_get_l1d_caches()->size + cpuinfo_get_l1i_caches()->size) / 1024 << " KB" << '\n'
        << "L2 cache(per core): " << cpuinfo_get_l2_caches()->size / 1024 << " KB" << '\n'
        << "L3 cache(shared): " << cpuinfo_get_l3_caches()->size / 1024 << " KB";
        if(cpuinfo_get_l4_caches_count()!=0) buf << "L4 cache(shared): " << cpuinfo_get_l4_caches()->size / 1024 << " KB";
        buf << "\n────────────────────────────\n"
        << "Supported features: " << get_features() << '\n';
    
    text->copy_label(buf.str().c_str());
    text->redraw();
    Fl::repeat_timeout(1, info);
}


int main(int argc, char *argv[]) {
    cpuinfo_initialize();

    

    Fl_Window *window = new Fl_Cairo_Window(480, 600, "CPU-INF");
    Fl::scheme("gleam");
    Fl::background(45, 45, 48);

    Fl::background2(30, 30, 30);

    Fl::foreground(240, 240, 240);

    Fl_Pixmap* raw = new Fl_Pixmap(_ae50a67a4b34082eef2d636c69fecbameRZ4QDRyYsbD7qv);
    Fl_RGB_Image* icon = new Fl_RGB_Image(raw);
    window->icon(icon);
    
    const struct cpuinfo_package *cpu = cpuinfo_get_package(0);
    std::string Name = cpu->name;
    std::string Vendor;

    const Fl_Color BG      = fl_rgb_color(45, 45, 48);
    const Fl_Color TAB_OFF = fl_rgb_color(37, 37, 38);
    const Fl_Color TAB_ON  = fl_rgb_color(0, 122, 204);   
    const Fl_Color TEXT    = fl_rgb_color(240, 240, 240);
    Fl_Tabs *tabs = new Fl_Tabs(0, 0, 480, 600);
    Fl_Group *page1 = new Fl_Group(0, 25, 480, 575, " CPU ");
    page1->box(FL_FLAT_BOX);
    page1->color(TAB_OFF);
    page1->selection_color(TAB_ON);
    page1->labelcolor(TEXT);

    
    {
        if (Name.contains("Intel")) {
            logo = new Fl_Pixmap(a7532d739e484bb0b8026fc3dee2c8fczbY8e1bcgFOGFION);
        } else if (Name.contains("AMD")) {
            logo = new Fl_Pixmap(_896298cf7884ce9b8b8925cc26ee1da9QPlpZag3dnKj3xm);
        } else if(CPUINFO_ARCH_ARM) {
            logo = new Fl_Pixmap(_d658913e4f1481fca4d8e42666191905vjjs7DCV0dOfPUI);
        }
        else {
            logo = new Fl_Pixmap(ac9272be786241c1873bd4107befbd7bBonTsxvp7JqUBHZ3);
        }
        if (logo) {
            image_box = new Fl_Box(176, 35, 128, 128);
            image_box->image(logo->copy(128, 128));
        }
        text = new Fl_Box(10, 170, 460, 420, "");
        text->labelsize(14);
        text->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP | FL_ALIGN_WRAP);
    }
    page1->end();


    Fl_Group *page2 = new Fl_Group(0, 25, 480, 575, " About ");
    page2->box(FL_FLAT_BOX);
    page2->color(TAB_OFF);
    page2->selection_color(TAB_ON);
    page2->labelcolor(TEXT);

    {
        about = new Fl_Box(10, 35, 460, 200,
            "CPU-INF 1.2\nBy Naharashu\nRepo: https://github.com/Naharashu/cpuinf");
        about->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP | FL_ALIGN_WRAP);
    }
    page2->end();
    tabs->end();
    window->end();
    window->show();

    Fl::add_timeout(1, info);

    return Fl::run();
}