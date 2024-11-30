//
// Created by Chase Nagle on 11/14/24.
//

#ifndef OPENGLPROJECT_FILEHELPERS_HPP
#define OPENGLPROJECT_FILEHELPERS_HPP


#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <iostream>
#include <vector>

#include <fstream>
#include <sstream>

#include <string>





static std::string getFilePath(const std::string& relativePath) {
#ifdef __APPLE__  // Use __APPLE__ instead of checking inside the function
    CFBundleRef bundle = CFBundleGetMainBundle();
    if (!bundle) {
        return "";  // Return empty string if bundle retrieval fails
    }

    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(bundle);
    if (!resourcesURL) {
        return "";  // Return empty string if resources URL retrieval fails
    }

    char path[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
        CFRelease(resourcesURL);  // Release resourcesURL after successful use
        return std::string(path) + "/" + relativePath;
    }

    CFRelease(resourcesURL);  // Ensure release in failure case
    return "";  // Return empty string if path couldn't be resolved
#else
    return relativePath;  // For non-macOS systems, just return the relative path
#endif
}

static std::string loadShaderSource(const std::string& filePath){
    std::string content;
    std::string path = getFilePath(filePath);
    std::ifstream source(path);
    if(!source.is_open()){
        throw std::runtime_error("Failed to find source file at" + path);
    }
    std::string line = "";
    while(!source.eof()){
        std::getline(source, line);
        content.append(line + '\n');
    }
    source.close();
    return content;
}










#endif //OPENGLPROJECT_FILEHELPERS_HPP
