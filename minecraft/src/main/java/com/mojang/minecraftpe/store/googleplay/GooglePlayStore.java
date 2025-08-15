package com.mojang.minecraftpe.store.googleplay;

import com.mojang.minecraftpe.MainActivity;
import com.mojang.minecraftpe.store.ExtraLicenseResponseData;
import com.mojang.minecraftpe.store.Store;
import com.mojang.minecraftpe.store.StoreListener;

public class GooglePlayStore implements Store {
    MainActivity mActivity;
    StoreListener mListener;

    public GooglePlayStore(MainActivity activity, String licenseKey, StoreListener listener) {
        mActivity = activity;
        mListener = listener;
        // Skip any license check, just tell client store is ready
        mListener.onStoreInitialized(true);
    }

    @Override
    public String getStoreId() {
        return "android.googleplay";
    }

    @Override
    public boolean hasVerifiedLicense() {
        return true; // Always licensed
    }

    @Override
    public boolean receivedLicenseResponse() {
        return true; // Pretend license check finished
    }

    @Override
    public void acknowledgePurchase(String receipt, String productType) {}

    @Override
    public void destructor() {}

    @Override
    public ExtraLicenseResponseData getExtraLicenseData() {
        return new ExtraLicenseResponseData(0L, 0L, 0L);
    }

    @Override
    public void purchase(String productId, boolean isSubscription, String payload) {}

    @Override
    public void purchaseGame() {}

    @Override
    public void queryProducts(String[] productIds) {}

    @Override
    public void queryPurchases() {}

    @Override
    public String getProductSkuPrefix() {
        return "";
    }

    @Override
    public String getRealmsSkuPrefix() {
        return "";
    }
}