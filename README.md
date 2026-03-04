# MEPA Sample Application for LAN8840 EDS2 Daughterboard

- This sample application is a reference code for running a single 1G PHY on SAMA7. It uses the following hardware:
    - LAN8840 EDS2 Daughter Card (https://www.microchip.com/en-us/development-tool/ev12n54a)
    - SAMA7D65 Curiosity Kit (https://www.microchip.com/en-us/development-tool/ev63j76a)
- Softwares used:
    - mdio-tools (mdio.c) and MDIO-NETLINK kernel module (https://github.com/wkz/mdio-tools) for MDIO BUS Access. 
    - MEPA code was referenced from repository https://github.com/MicrochipTech/mepa-app-malibu10-rpi.
    - v2025.12 sw-mepa (https://github.com/microchip-ung/sw-mepa)

- This is used as a starting point when developing own application. Used for sanity checking, example code includes simple IO test, simple mepa init, basic port information, and basic port polling.
- Note: This is not a production code! Please use only as a reference.

### CMake Flags:

- `-DCMAKE_TOOLCHAIN_FILE` - part of Buildroot SDK or Yocto SDK.ls
    - Make sure to supply `toolchainfile.cmake` or `*-toolchain.cmake` otherwise it will build natively.

## Test Setup
- LAN8840 PHY Daughterboard connected to SAMA7D65 Curiosity Kit EDS2 Connector.
- Make sure that `mdio-netlink` kernel module (part of wkz/mdio-tools) is installed in target platform.
    - In buildroot, it can be added in buildroot configuration. Or mdio-netlink can be built natively. (https://github.com/wkz/mdio-tools/tree/master/kernel)
- Make sure device tree overlay is added in BSP as follows.
````
&gmac1 {
    #address-cells = <1>;
    #size-cells = <0>;
    phy-mode = "rgmii-id";
    status = "okay";

    // Fix MAC at 1000Mbps
    fixed-link {
        speed = <1000>;
        full-duplex;
    };

    // Add mdio to appear in mdio-tools
    mdio {
        #address-cells = <1>;
        #size-cells = <0>;

        // Make sure disabled status of PHY connected to EDS2 to avoid loading drivers. 
        // In this case, PHYAD = 1 because of @1 & reg = <1>;
        ethernet-phy@1 {
            reg = <1>;
            status = "disabled";
        };
    };
};

````
## Prepare Environment
1. Go to repository root directory 
    - `$ cd ./mepa-app-lan8840-sama7d65-eds2/`
2. Initialize submodules if cloned.
    - `$ git submodule init`
    - `$ git submodule update`
3. The app was build on sw-mepa v2025.12 and uses mesa v2025.09
    - Check MESA version dependency of sw-mepa using:
        - `$ cat ./sw-mepa/.cmake/deps-mesa.json`
    - Clone required MESA version and place in ./sw-mepa/ 
        - `$ git clone https://github.com/microchip-ung/mesa --branch=v2025.09 --depth=1 ./sw-mepa/sw-mesa/`
3. **[Optional]** Download cross toolchain or skip this step if building natively.
    - Linux4Microchip cross toolchains (https://developerhelp.microchip.com/xwiki/bin/view/applications/linux4sam/components/softwaretools/)
    - **Buildroot SDK - 2025.02 (Linux4SAM 2025.04) - SAMA7**
        1. Download SDK
            - `$ wget https://ww1.microchip.com/downloads/aemdocuments/documents/mpu32-direct/pub/demo/linux4sam-2025.04/linux4sam-buildroot-Cortex-A7-sdk-2025.04.tar.gz` 
        2. Extract somewhere. Make sure extract dir only has user rights. Example here is /opt/mchp/.
            - `$ tar -xvf ./linux4sam-buildroot-Cortex-A7-sdk-2025.04.tar.gz -C /opt/mchp/`
        3. Relocate SDK. Root rights NOT required.
            - `$ /opt/mchp/arm-buildroot-linux-gnueabihf_sdk-buildroot/relocate-sdk.sh`
    - **Yocto Project 5.0.4 - scarthgap (Linux4Microchip 2025.04) - SAMA7** *(`NOT WORKING`, See notes in build instructions for yocto)*
        1. Download SDK
            - `$ wget https://ww1.microchip.com/downloads/aemdocuments/documents/mpu32-direct/pub/demo/yocto-sdk/linux4sam-oecore-Cortex-A7-sdk-2025.04.sh`
        2. Create folder somewhere to install yocto SDK toolchain. Example here is /opt/mchp/yocto-sdk-sama7/
            - `$ mkdir /opt/mchp/yocto-sdk-sama7/`
        3. Give execute command and run .sh.
            - `$ chmod 775 ./linux4sam-oecore-Cortex-A7-sdk-2025.04.sh`
            - `$ ./linux4sam-oecore-Cortex-A7-sdk-2025.04.sh`
        4. Make sure to set your install directory.
            ```
            Enter target directory for SDK (default: /usr/local/oecore-x86_64): /opt/mchp/yocto-sdk-sama7/
            You are about to install the SDK to "/opt/mchp/yocto-sdk-sama7". Proceed [Y/n]? Y
            ```
## Build Instructions

1. Create a cmake build directory and change to it.
    - `$ cd ./mepa-app-lan8840-sama7d65-eds2/`
    - `$ mkdir ./build/`
    - `$ cd ./build/`
2. Create a CMake Project and make sure to add toolchain if cross compiling.
    - If using Buildroot SDK:
        - `$ cmake ../mepa_app_sanity_check_standalone_lan884x/ -DCMAKE_TOOLCHAIN_FILE=$(find /opt/mchp/arm-buildroot-linux-gnueabihf_sdk-buildroot -name "toolchainfile.cmake")`
        - Note: `find` command is used to easily find toolchainfile.cmake.
    - If using Yocto SDK:
        - `$ cmake ../mepa_app_sanity_check_standalone_lan884x/ -DCMAKE_TOOLCHAIN_FILE=$(find /opt/mchp/yocto-sdk-sama7 -name "*-toolchain.cmake")`
        - **Note:** This will fail since this app requires `libmnl` which is not part of Yocto SDK. Command was provided in case user has built their custom yocto SDK.
3. Run `$ make`

## Expected Build Output
- See docs/build_log.txt; contains buildroot and yocto output.
## Expected Application Output
- See docs/app_log.txt