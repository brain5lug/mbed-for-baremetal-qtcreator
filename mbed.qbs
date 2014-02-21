import qbs 1.0

Product {
    type: "application"
    Depends { name:"cpp" }
    property string mbed: "mbed-src/"
    property string rtos: "mbed-rtos/"
    property string vendor: "STM"
    property string model: "STM32F4DISCOVERY"
    property string toolchain: "GCC_ARM"
    property string cortex: "M4"
    cpp.positionIndependentCode: false
    cpp.debugInformation: true
    cpp.commonCompilerFlags: [
    	"-mthumb","-mcpu=cortex-m4","-mfloat-abi=hard","-mfpu=fpv4-sp-d16",
      "-fdata-sections","-ffunction-sections","-fno-inline","-std=c99"]
    cpp.linkerFlags:[
        "-mthumb","-mcpu=cortex-m4","-mfloat-abi=hard","-mfpu=fpv4-sp-d16","--specs=nano.specs",
        "-Wl,--gc-sections","-T",path+"/"+mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+model+"/TOOLCHAIN_"+toolchain+"/STM32F407.ld","-lgcc","-lc"]
    cpp.includePaths: [
    	mbed+"api",
    	mbed+"hal",
      mbed+"targets/cmsis/",
      mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+model+"/",
      mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+model+"/"
    ]
    files: [
    	mbed+"api/*.h",
    	mbed+"common/*",
    	mbed+"hal/*.h",
    	mbed+"targets/cmsis/*.h",
    	mbed+"targets/cmsis/core_cm4_simd.h",
    	mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+model+"/*",
    	mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+model+"/TOOLCHAIN_"+toolchain+"/*",
    	mbed+"targets/cmsis/target/*.h",
    	mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+model+"/*",
      "main.cpp"
    ]
    Properties {
        condition: qbs.buildVariant === "debug"
        cpp.defines: outer.concat(["DEBUG=1"])
    }
    Group {
        qbs.install: true
        fileTagsFilter: "application"
    }
}
