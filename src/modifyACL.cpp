#include "modifyACL.hpp"


int lockFolder(const std::string& folderPath) {
    std::wstring wideFolderPath(folderPath.begin(), folderPath.end());

    PSECURITY_DESCRIPTOR pSD = NULL;

    DWORD result = GetNamedSecurityInfoW(
        wideFolderPath.c_str(),
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL,
        NULL,
        NULL,
        NULL,
        &pSD);

    if (result != ERROR_SUCCESS) {
        std::cerr << "Error: Could not retrieve folder security info. Error code: " << result << "\n";
        return 0;
    }

  
    EXPLICIT_ACCESSW ea = {};
    ea.grfAccessPermissions = GENERIC_ALL;
    ea.grfAccessMode = DENY_ACCESS;
    ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
    ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
    ea.Trustee.ptstrName = const_cast<LPWSTR>(L"EVERYONE");

    PACL pNewDACL = NULL;
    result = SetEntriesInAclW(1, &ea, NULL, &pNewDACL);

    if (result != ERROR_SUCCESS) {
        std::cerr << "Error: Could not create new DACL. Error code: " << result << "\n";
        return 0;
    }

    result = SetNamedSecurityInfoW(
        const_cast<LPWSTR>(wideFolderPath.c_str()),
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL,
        NULL,
        pNewDACL,
        NULL);




    if (result != ERROR_SUCCESS) {
        return 1;
    }
    else {
        if (pNewDACL) {
            LocalFree(pNewDACL);
        }
        return 0;
    }


}

int unlockFolder(const std::string& folderPath) {
    
    std::wstring wideFolderPath(folderPath.begin(), folderPath.end());


    DWORD result = SetNamedSecurityInfoW(
        const_cast<LPWSTR>(wideFolderPath.c_str()),
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL,
        NULL,
        NULL,
        NULL);

    if (result != ERROR_SUCCESS) {
        return 0;
    }
    else {
        return 1;
    }
}
