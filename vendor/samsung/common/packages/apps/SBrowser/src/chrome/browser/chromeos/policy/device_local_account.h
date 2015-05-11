// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_LOCAL_ACCOUNT_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_LOCAL_ACCOUNT_H_

#include <string>
#include <vector>

namespace chromeos {
class CrosSettings;
}

namespace policy {

// This must match DeviceLocalAccountInfoProto.AccountType in
// chrome_device_policy.proto.
struct DeviceLocalAccount {
  enum Type {
    // A login-less, policy-configured browsing session.
    TYPE_PUBLIC_SESSION,
    // An account that serves as a container for a single full-screen app.
    TYPE_KIOSK_APP,
    // Sentinel, must be last.
    TYPE_COUNT
  };

  DeviceLocalAccount(Type type,
                     const std::string& account_id,
                     const std::string& kiosk_app_id);
  ~DeviceLocalAccount();

  Type type;
  // A device-local account has two identifiers:
  // * The |account_id| is chosen by the entity that defines the device-local
  //   account. The only constraints are that the |account_id| be unique and,
  //   for legacy reasons, it contain an @ symbol.
  // * The |user_id| is a synthesized identifier that is guaranteed to be
  //   unique, contain an @ symbol, not collide with the |user_id| of any other
  //   user on the device (such as regular users or supervised users) and be
  //   identifiable as belonging to a device-local account by.
  // The |account_id| is primarily used by policy code: If device policy defines
  // a device-local account with a certain |account_id|, the user policy for
  // that account has to be fetched by referencing the same |account_id|.
  // The |user_id| is passed to the chromeos::UserManager where it becomes part
  // of the global user list on the device. The |account_id| would not be safe
  // to use here as it is a free-form identifier that could conflict with
  // another |user_id| on the device and cannot be easily identified as
  // belonging to a device-local account.
  std::string account_id;
  std::string user_id;
  std::string kiosk_app_id;
};

std::string GenerateDeviceLocalAccountUserId(const std::string& account_id,
                                             DeviceLocalAccount::Type type);

// Determines whether |user_id| belongs to a device-local account and if so,
// returns the type of device-local account in |type| unless |type| is NULL.
bool IsDeviceLocalAccountUser(const std::string& user_id,
                              DeviceLocalAccount::Type* type);

// Stores a list of device-local accounts in |cros_settings|. The accounts are
// stored as a list of dictionaries with each dictionary containing the
// information about one |DeviceLocalAccount|.
void SetDeviceLocalAccounts(
    chromeos::CrosSettings* cros_settings,
    const std::vector<DeviceLocalAccount>& accounts);

// Retrieves a list of device-local accounts from |cros_settings|.
std::vector<DeviceLocalAccount> GetDeviceLocalAccounts(
    chromeos::CrosSettings* cros_settings);

}  // namespace policy

#endif  // CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_LOCAL_ACCOUNT_H_