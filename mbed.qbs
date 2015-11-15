import qbs 1.0

Product {
    type: "application"
    Depends { name:"cpp" }
    property string mbed: "mbed-src/"
    property string rtos: "mbed-rtos/"
    property string vendor: "STM"
    property string chip: "STM32F4"
    property string fullchip: "STM32F407VG"
    property string model: "DISCO_F407VG"
    property string toolchain: "GCC_ARM"
    property string cortex: "M4"
    cpp.defines: ["TOOLCHAIN_GCC_CW=1"]
    cpp.positionIndependentCode: false
    cpp.debugInformation: true
    cpp.commonCompilerFlags: [
        "-mthumb","-march=armv7e-m","-mfloat-abi=hard","-mfpu=fpv4-sp-d16",
      "-fdata-sections","-ffunction-sections","-fno-inline","-std=c99","-flto","-fno-rtti","-fexceptions"]
    cpp.linkerFlags:[
        "-flto","-mthumb","-march=armv7e-m","-mfloat-abi=hard","-mfpu=fpv4-sp-d16","--specs=nano.specs","-Wl,--start-group",
        "-Wl,--gc-sections","-T",path+"/"+mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/"+"/TARGET_"+fullchip+"/TOOLCHAIN_"+toolchain+"/STM32F407XG.ld","-lnosys","-lgcc","-lc"]
    cpp.includePaths: [
      mbed+"api",
    	mbed+"hal",
      mbed+"targets/cmsis/",
      mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/",
      mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/TARGET_"+fullchip+"/",
      mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+chip+"/",
      mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+chip+"/TARGET_"+model+"/",
      mbed+"devices/lis302/"
    ]
    files: [
    	mbed+"api/*.h",
        mbed+"common/*",
    	mbed+"hal/*.h",
    	mbed+"targets/cmsis/*.h",
        //mbed+"targets/cmsis/core_cm4_simd.h",
        mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/*",
        mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/TARGET_"+fullchip+"/*",
        mbed+"targets/cmsis/TARGET_"+vendor+"/TARGET_"+chip+"/TARGET_"+fullchip+"/TOOLCHAIN_"+toolchain+"/*",
    	mbed+"targets/cmsis/target/*.h",
        mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+chip+"/*",
        mbed+"targets/hal/TARGET_"+vendor+"/TARGET_"+chip+"/TARGET_"+model+"/*",
      mbed+"devices/lis302/*",
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
