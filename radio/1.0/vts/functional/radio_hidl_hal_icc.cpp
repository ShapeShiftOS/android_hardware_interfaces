/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/logging.h>
#include <radio_hidl_hal_utils_v1_0.h>

/*
 * Test IRadio.getIccCardStatus() for the response returned.
 */
TEST_P(RadioHidlTest, getIccCardStatus) {
    LOG(DEBUG) << "getIccCardStatus";
    EXPECT_LE(cardStatus.applications.size(), (unsigned int)RadioConst::CARD_MAX_APPS);
    EXPECT_LT(cardStatus.gsmUmtsSubscriptionAppIndex, (int)RadioConst::CARD_MAX_APPS);
    EXPECT_LT(cardStatus.cdmaSubscriptionAppIndex, (int)RadioConst::CARD_MAX_APPS);
    EXPECT_LT(cardStatus.imsSubscriptionAppIndex, (int)RadioConst::CARD_MAX_APPS);
    LOG(DEBUG) << "getIccCardStatus finished";
}

/*
 * Test IRadio.supplyIccPinForApp() for the response returned
 */
TEST_P(RadioHidlTest, supplyIccPinForApp) {
    LOG(DEBUG) << "supplyIccPinForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->supplyIccPinForApp(serial, hidl_string("test1"),
                                      cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(CheckAnyOfErrors(
                radioRsp->rspInfo.error,
                {RadioError::PASSWORD_INCORRECT, RadioError::REQUEST_NOT_SUPPORTED}));
        }
    }
    LOG(DEBUG) << "supplyIccPinForApp finished";
}

/*
 * Test IRadio.supplyIccPukForApp() for the response returned.
 */
TEST_P(RadioHidlTest, supplyIccPukForApp) {
    LOG(DEBUG) << "supplyIccPukForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->supplyIccPukForApp(serial, hidl_string("test1"), hidl_string("test2"),
                                      cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(CheckAnyOfErrors(radioRsp->rspInfo.error, {RadioError::PASSWORD_INCORRECT,
                                                                   RadioError::INVALID_SIM_STATE}));
        }
    }
    LOG(DEBUG) << "supplyIccPukForApp finished";
}

/*
 * Test IRadio.supplyIccPin2ForApp() for the response returned.
 */
TEST_P(RadioHidlTest, supplyIccPin2ForApp) {
    LOG(DEBUG) << "supplyIccPin2ForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->supplyIccPin2ForApp(serial, hidl_string("test1"),
                                       cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(
                CheckAnyOfErrors(radioRsp->rspInfo.error,
                                 {RadioError::PASSWORD_INCORRECT, RadioError::REQUEST_NOT_SUPPORTED,
                                  RadioError::SIM_PUK2}));
        }
    }
    LOG(DEBUG) << "supplyIccPin2ForApp finished";
}

/*
 * Test IRadio.supplyIccPuk2ForApp() for the response returned.
 */
TEST_P(RadioHidlTest, supplyIccPuk2ForApp) {
    LOG(DEBUG) << "supplyIccPuk2ForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->supplyIccPuk2ForApp(serial, hidl_string("test1"), hidl_string("test2"),
                                       cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(CheckAnyOfErrors(radioRsp->rspInfo.error, {RadioError::PASSWORD_INCORRECT,
                                                                   RadioError::INVALID_SIM_STATE}));
        }
    }
    LOG(DEBUG) << "supplyIccPuk2ForApp finished";
}

/*
 * Test IRadio.changeIccPinForApp() for the response returned.
 */
TEST_P(RadioHidlTest, changeIccPinForApp) {
    LOG(DEBUG) << "changeIccPinForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->changeIccPinForApp(serial, hidl_string("test1"), hidl_string("test2"),
                                      cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(CheckAnyOfErrors(
                radioRsp->rspInfo.error,
                {RadioError::PASSWORD_INCORRECT, RadioError::REQUEST_NOT_SUPPORTED}));
        }
    }
    LOG(DEBUG) << "changeIccPinForApp finished";
}

/*
 * Test IRadio.changeIccPin2ForApp() for the response returned.
 */
TEST_P(RadioHidlTest, changeIccPin2ForApp) {
    LOG(DEBUG) << "changeIccPin2ForApp";
    serial = GetRandomSerialNumber();

    // Pass wrong password and check PASSWORD_INCORRECT returned for 3GPP and
    // 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->changeIccPin2ForApp(serial, hidl_string("test1"), hidl_string("test2"),
                                       cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            ASSERT_TRUE(
                CheckAnyOfErrors(radioRsp->rspInfo.error,
                                 {RadioError::PASSWORD_INCORRECT, RadioError::REQUEST_NOT_SUPPORTED,
                                  RadioError::SIM_PUK2}));
        }
    }
    LOG(DEBUG) << "changeIccPin2ForApp finished";
}

/*
 * The following test is disabled due to b/109889468
 *
 * Test IRadio.getImsiForApp() for the response returned.
 */
TEST_P(RadioHidlTest, DISABLED_getImsiForApp) {
    LOG(DEBUG) << "DISABLED_getImsiForApp";
    serial = GetRandomSerialNumber();

    // Check success returned while getting imsi for 3GPP and 3GPP2 apps only
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        if (cardStatus.applications[i].appType == AppType::SIM ||
            cardStatus.applications[i].appType == AppType::USIM ||
            cardStatus.applications[i].appType == AppType::RUIM ||
            cardStatus.applications[i].appType == AppType::CSIM) {
            radio->getImsiForApp(serial, cardStatus.applications[i].aidPtr);
            EXPECT_EQ(std::cv_status::no_timeout, wait());
            EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
            EXPECT_EQ(serial, radioRsp->rspInfo.serial);
            ASSERT_TRUE(
                CheckAnyOfErrors(radioRsp->rspInfo.error, {RadioError::NONE}, CHECK_GENERAL_ERROR));

            // IMSI (MCC+MNC+MSIN) is at least 6 digits, but not more than 15
            if (radioRsp->rspInfo.error == RadioError::NONE) {
                EXPECT_NE(radioRsp->imsi, hidl_string());
                EXPECT_GE((int)(radioRsp->imsi).size(), 6);
                EXPECT_LE((int)(radioRsp->imsi).size(), 15);
            }
        }
    }
    LOG(DEBUG) << "DISABLED_getImsiForApp finished";
}

/*
 * Test IRadio.iccIOForApp() for the response returned.
 */
TEST_P(RadioHidlTest, iccIOForApp) {
    LOG(DEBUG) << "iccIOForApp";
    serial = GetRandomSerialNumber();

    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        IccIo iccIo;
        iccIo.command = 0xc0;
        iccIo.fileId = 0x6f11;
        iccIo.path = hidl_string("3F007FFF");
        iccIo.p1 = 0;
        iccIo.p2 = 0;
        iccIo.p3 = 0;
        iccIo.data = hidl_string();
        iccIo.pin2 = hidl_string();
        iccIo.aid = cardStatus.applications[i].aidPtr;

        radio->iccIOForApp(serial, iccIo);
        EXPECT_EQ(std::cv_status::no_timeout, wait());
        EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
        EXPECT_EQ(serial, radioRsp->rspInfo.serial);
    }
    LOG(DEBUG) << "iccIOForApp finished";
}

/*
 * Test IRadio.iccTransmitApduBasicChannel() for the response returned.
 */
TEST_P(RadioHidlTest, iccTransmitApduBasicChannel) {
    LOG(DEBUG) << "iccTransmitApduBasicChannel";
    serial = GetRandomSerialNumber();
    SimApdu msg;
    memset(&msg, 0, sizeof(msg));
    msg.data = hidl_string();

    radio->iccTransmitApduBasicChannel(serial, msg);
    EXPECT_EQ(std::cv_status::no_timeout, wait());
    EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
    EXPECT_EQ(serial, radioRsp->rspInfo.serial);

    // TODO(sanketpadawe): Add test for error code
    LOG(DEBUG) << "iccTransmitApduBasicChannel finished";
}

/*
 * Test IRadio.iccOpenLogicalChannel() for the response returned.
 */
TEST_P(RadioHidlTest, iccOpenLogicalChannel) {
    LOG(DEBUG) << "iccOpenLogicalChannel";
    serial = GetRandomSerialNumber();
    int p2 = 0x04;
    // Specified in ISO 7816-4 clause 7.1.1 0x04 means that FCP template is requested.
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        radio->iccOpenLogicalChannel(serial, cardStatus.applications[i].aidPtr, p2);
        EXPECT_EQ(std::cv_status::no_timeout, wait());
        EXPECT_EQ(serial, radioRsp->rspInfo.serial);
        EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
    }
    LOG(DEBUG) << "iccOpenLogicalChannel finished";
}

/*
 * Test IRadio.iccCloseLogicalChannel() for the response returned.
 */
TEST_P(RadioHidlTest, iccCloseLogicalChannel) {
    LOG(DEBUG) << "iccCloseLogicalChannel";
    serial = GetRandomSerialNumber();
    // Try closing invalid channel and check INVALID_ARGUMENTS returned as error
    radio->iccCloseLogicalChannel(serial, 0);
    EXPECT_EQ(std::cv_status::no_timeout, wait());
    EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
    EXPECT_EQ(serial, radioRsp->rspInfo.serial);

    EXPECT_EQ(RadioError::INVALID_ARGUMENTS, radioRsp->rspInfo.error);
    LOG(DEBUG) << "iccCloseLogicalChannel finished";
}

/*
 * Test IRadio.iccTransmitApduLogicalChannel() for the response returned.
 */
TEST_P(RadioHidlTest, iccTransmitApduLogicalChannel) {
    LOG(DEBUG) << "iccTransmitApduLogicalChannel";
    serial = GetRandomSerialNumber();
    SimApdu msg;
    memset(&msg, 0, sizeof(msg));
    msg.data = hidl_string();

    radio->iccTransmitApduLogicalChannel(serial, msg);
    EXPECT_EQ(std::cv_status::no_timeout, wait());
    EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
    EXPECT_EQ(serial, radioRsp->rspInfo.serial);

    // TODO(sanketpadawe): Add test for error code
    LOG(DEBUG) << "iccTransmitApduLogicalChannel finished";
}

/*
 * Test IRadio.requestIccSimAuthentication() for the response returned.
 */
TEST_P(RadioHidlTest, requestIccSimAuthentication) {
    LOG(DEBUG) << "requestIccSimAuthentication";
    serial = GetRandomSerialNumber();

    // Pass wrong challenge string and check RadioError::INVALID_ARGUMENTS
    // or REQUEST_NOT_SUPPORTED returned as error.
    for (int i = 0; i < (int)cardStatus.applications.size(); i++) {
        radio->requestIccSimAuthentication(serial, 0, hidl_string("test"),
                                           cardStatus.applications[i].aidPtr);
        EXPECT_EQ(std::cv_status::no_timeout, wait());
        EXPECT_EQ(serial, radioRsp->rspInfo.serial);
        EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
        ASSERT_TRUE(CheckAnyOfErrors(radioRsp->rspInfo.error, {RadioError::INVALID_ARGUMENTS,
                                                               RadioError::REQUEST_NOT_SUPPORTED}));
    }
    LOG(DEBUG) << "requestIccSimAuthentication finished";
}

/*
 * Test IRadio.supplyNetworkDepersonalization() for the response returned.
 */
TEST_P(RadioHidlTest, supplyNetworkDepersonalization) {
    LOG(DEBUG) << "supplyNetworkDepersonalization";
    serial = GetRandomSerialNumber();

    radio->supplyNetworkDepersonalization(serial, hidl_string("test"));
    EXPECT_EQ(std::cv_status::no_timeout, wait());
    EXPECT_EQ(RadioResponseType::SOLICITED, radioRsp->rspInfo.type);
    EXPECT_EQ(serial, radioRsp->rspInfo.serial);

    if (cardStatus.cardState == CardState::ABSENT) {
        ASSERT_TRUE(CheckAnyOfErrors(
            radioRsp->rspInfo.error,
            {RadioError::NONE, RadioError::INVALID_ARGUMENTS, RadioError::INTERNAL_ERR,
             RadioError::INVALID_SIM_STATE, RadioError::MODEM_ERR, RadioError::NO_MEMORY,
             RadioError::PASSWORD_INCORRECT, RadioError::SIM_ABSENT, RadioError::SYSTEM_ERR}));
    }
    LOG(DEBUG) << "supplyNetworkDepersonalization finished";
}
